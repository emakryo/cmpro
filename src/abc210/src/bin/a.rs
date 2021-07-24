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
        a: usize,
        x: usize,
        y: usize,
    }

    if n > a {
        println!("{}", a*x + (n-a)*y);
    } else {
        println!("{}", n*x);
    }
}