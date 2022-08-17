#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;
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

    let mut t = vec![];
    let mut a = vec![];
    for _ in 0..n {
        proconio::input! {
            ti: usize,
            ki: usize,
            ai: [usize; ki],
        }

        t.push(ti);
        a.push(ai);
    }

    let mut visit = vec![false; n];
    visit[n-1] = true;
    let mut ans = 0;

    for i in (0..n).rev() {
        if visit[i] {
            ans += t[i];
            for &j in &a[i] {
                visit[j-1] = true;
            }
        }
    }

    println!("{}", ans);
}