#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;
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
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        xs: [(usize, usize); n],
    }

    let mut memo = vec![vec![None; 101]; 101];

    if rec(1, 100, &mut memo, &xs) == 0 {
        println!("Bob");
    } else {
        println!("Alice");
    }
}

fn rec(l: usize, r: usize, memo: &mut Vec<Vec<Option<i32>>>, xs: &Vec<(usize, usize)>) -> i32 {
    if let Some(x) = memo[l][r] {
        return x;
    }
    if r <= l {
        memo[l][r] = Some(0);
        return 0;
    }
    let mut g = HashSet::new();
    for &(a, b) in xs {
        if l <= a && b <= r {
            g.insert(rec(l, a, memo, xs) ^ rec(b, r, memo, xs));
        }
    }

    let mut ret = 0;
    for i in 0..200 {
        if !g.contains(&i) {
            ret = i;
            break;
        }
    }

    memo[l][r] = Some(ret);
    ret
}
