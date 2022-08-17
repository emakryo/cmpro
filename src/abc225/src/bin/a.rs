#![allow(unused_macros, unused_imports)]

use proconio::marker::Chars;
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
        mut s: Chars
    }
    s.sort();
    s.dedup();

    if s.len() == 1 {
        println!("1");
    } else if s.len() == 2 {
        println!("3");
    } else {
        println!("6");
    }
}