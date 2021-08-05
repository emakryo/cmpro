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
    }

    for i in 0..n {
        println!("{} {}", (2*i+1)%n+1, (2*i+2)%n+1);
    }
}