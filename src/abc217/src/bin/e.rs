#![allow(unused_macros, unused_imports)]

use std::collections::{BinaryHeap, VecDeque};
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

    let mut s = BinaryHeap::<i64>::new();
    let mut t = VecDeque::new();


    for _ in 0..q {
        proconio::input! { c: usize }
        if c == 1 {
            proconio::input! { x: i64 }
            t.push_back(x);
        } else if c == 2 {
            if let Some(x) = s.pop() {
                println!("{}", -x);
            } else {
                let x = t.pop_front().unwrap();
                println!("{}", x);
            }
        } else {
            for x in t.drain(..) {
                s.push(-x);
            }
        }
    }
}