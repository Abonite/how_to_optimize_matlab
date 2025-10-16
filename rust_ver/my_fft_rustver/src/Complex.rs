#[derive(Clone, Copy)]
pub struct myComplex {
    pub re: f64,
    pub im: f64,
}

impl myComplex {
    pub fn newDescartes(re: f64, im: f64) -> Self {
        myComplex { re, im }
    }

    pub fn newPolar(r: f64, theta: f64) -> Self {
        myComplex {
            re: r * theta.cos(),
            im: r * theta.sin(),
        }
    }
}

pub fn addComplex(a: &myComplex, b: &myComplex) -> myComplex {
    myComplex {
        re: a.re + b.re,
        im: a.im + b.im,
    }
}

pub fn subComplex(a: &myComplex, b: &myComplex) -> myComplex {
    myComplex {
        re: a.re - b.re,
        im: a.im - b.im,
    }
}

pub fn mulComplex(a: &myComplex, b: &myComplex) -> myComplex {
    myComplex {
        re: a.re * b.re - a.im * b.im,
        im: a.re * b.im + a.im * b.re,
    }
}

pub fn divComplex(a: &myComplex, b: &myComplex) -> myComplex {
    let denom = b.re * b.re + b.im * b.im;
    myComplex {
        re: (a.re * b.re + a.im * b.im) / denom,
        im: (a.im * b.re - a.re * b.im) / denom,
    }
}