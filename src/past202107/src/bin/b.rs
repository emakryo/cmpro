#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        a: f64,
        b: f64,
        c: f64,
    }

    println!("{}", c.min(a/b));
}