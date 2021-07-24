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
        n: usize,
        v: [i64; 2*n],
    }

    let mut pq = BinaryHeap::new();
    let mut ans = v.iter().sum::<i64>();
    for i in 0..n {
        pq.push(-v[n+i]);
        pq.push(-v[n-i-1]);
        ans += pq.pop().unwrap();
    }

    println!("{}", ans);
}