#![allow(unused_macros, unused_imports)]

use std::collections::BinaryHeap;
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
        q: usize,
    }

    let mut a = 0;
    let mut h = BinaryHeap::new();

    for _ in 0..q {
        proconio::input!{
            t: usize,
        }

        if t == 1 {
            proconio::input! { x: i64 }
            h.push(-x+a);
        } else if t == 2 {
            proconio::input! { x: i64 }
            a += x;
        } else {
            let x = h.pop().unwrap();
            println!("{}", -x+a);
        }
    }
}