mod Complex;

use Complex::{myComplex, addComplex, subComplex, mulComplex};

// fn main() {
    // let test_source = vec![
        // myComplex::newDescartes(1.0, 0.0),
        // myComplex::newDescartes(2.0, 0.0),
        // myComplex::newDescartes(3.0, 0.0),
        // myComplex::newDescartes(4.0, 0.0),
    // ];
// 
    // let result = my_fft_rustvar(test_source);
    // for c in result {
        // println!("{} + {}i", c.re, c.im);
    // }
// }

fn bin_reverse(fft_layer: usize) -> Vec<usize> {
    let size: usize = 1 << fft_layer;
    let mut result: Vec<usize> = vec![0; size];

    for i in 0..size {
        let mut temp: usize = 0;
        for j in 0..fft_layer {
            if (i & (1 << j)) != 0 {
                temp |= 1 << (fft_layer - 1 - j);
            }
        }
        result[i] = temp;
    }
    result
}

fn butterfly(a: myComplex, b: myComplex, w: myComplex) -> (myComplex, myComplex) {
    let t = mulComplex(&w, &b);
    let new_a = addComplex(&a.clone(), &t);
    let new_b = subComplex(&a.clone(), &t);
    (new_a, new_b)
}

fn subo(data: &[myComplex], gap: usize) -> Vec<myComplex> {
    let loop_t: usize = data.len() >> 1;
    let mut result: Vec<myComplex> = vec![myComplex::newDescartes(0.0, 0.0); data.len()];
    let N = gap << 1;
    for i in 0..loop_t {
        let w = myComplex::newPolar(1.0, -2.0 * std::f64::consts::PI * (i as f64) / (N as f64));
        let (new_a, new_b) = butterfly(data[i], data[i + gap], w);
        result[i] = new_a;
        result[i + gap] = new_b;
    }
    result
}

#[no_mangle]
pub extern "C" fn my_fft_rustvar(data: Vec<myComplex>) -> Vec<myComplex> {
    let fft_layer: usize = (data.len() as f64).log2() as usize;
    let bit_rev = bin_reverse(fft_layer);
    let mut data_reordered: Vec<myComplex> = vec![myComplex::newDescartes(0.0, 0.0); data.len()];
    for i in 0..data.len() {
        data_reordered[i] = data[bit_rev[i]];
    }

    for i in 0..fft_layer {
        let gap: usize = 1 << i;
        let sub_l: usize = 1 << (i + 1);
        for j in (0..data.len()).step_by(gap << 1) {
            let temp = &data_reordered.clone()[j..j + sub_l];
            data_reordered[j..j + sub_l].copy_from_slice(&subo(temp, gap));
        }
    }
    data_reordered
}
