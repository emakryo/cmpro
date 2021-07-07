#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        c: f64,
        ps: [(f64, f64); n],
    }

    let mean = ps.iter().map(|x| x.0).sum::<f64>() / n as f64;

    let ans = ps.iter().map(|x| {
        (x.0 - mean).hypot(x.1 - c).powi(2)
    }).sum::<f64>();

    println!("{}", ans);
}