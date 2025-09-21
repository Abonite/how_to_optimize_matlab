pub struct Complex {
    real: f64,
    imag: f64
}

impl Complex {
    pub fn new(real: f64, imag: f64) -> Self {
        Self { real, imag }
    }

    pub fn add(&self, other: &Complex) -> Complex {
        Complex {
            real: self.real + other.real,
            imag: self.imag + other.imag,
        }
    }

    pub fn sub(&self, other: &Complex) -> Complex {
        Complex {
            real: self.real - other.real,
            imag: self.imag - other.imag,
        }
    }

    pub fn mul(&self, other: &Complex) -> Complex {
        Complex {
            real: self.real * other.real - self.imag * other.imag,
            imag: self.real * other.imag + self.imag * other.real,
        }
    }

    pub fn div(&self, other: &Complex) -> Complex {
        denom: f64 = other.real * other.real + other.imag * other.imag;
        numer_real: f64 = self.real * other.real + self.imag * other.imag;
        numer_imag: f64 = self.imag * other.real - self.real * other.imag
        Complex {
            real: numer_real / denom,
            imag: numer_imag / denom
        }
    }

    pub fn integer_pow(&self, int times) {
        if times == 0 {
            return Complex::new(1.0, 0.0);
        } else {
            let mut result = Complex::new(self.real, self.imag);
            for _ in 0..times {
                result = result.mul(self);
            }
            return result;
        }
    }
}