#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(f64, f64); n],
    }

    let mut t = vec![0.0; n];
    let mut s = 0.0;

    for (i, &(a, b)) in xs.iter().enumerate() {
        t[i] = a / b;
        s += t[i];
    }

    let mut r = 0.0;
    let mut d = 0.0;
    for i in 0..n {
        r += t[i];
        if r >= s / 2.0 {
            d += (s / 2.0 - r + t[i]) * xs[i].1;
            break;
        }
        d += xs[i].0;
        dbg!(d);
    }

    println!("{}", d);
}