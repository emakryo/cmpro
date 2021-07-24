#![allow(unused_macros, unused_imports)]

use proconio::marker::{Bytes, Chars};
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
        s: Chars,
    }

    for i in 0..n {
        if s[i] == '1' {
            if i%2 == 0 {
                println!("Takahashi");
            } else {
                println!("Aoki");
            }
            return;
        }
    }
}