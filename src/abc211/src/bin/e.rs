#![allow(unused_macros, unused_imports)]

use std::{collections::HashSet, usize};

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
        n: usize,
        k: usize,
        s: [Chars; n],
    }

    let mut t = 0u64;
    for i in 0..n {
        for j in 0..n {
            if s[i][j] == '#' {
                t += 1 << (i*n+j);
            }
        }
    }

    let mut x = HashSet::new();
    dfs(0, t, n, k, &mut x);

    let ans = x.iter().filter(|x| x.count_ones() == k as u32).count();
    println!("{}", ans);
}

fn dfs(s: u64, mask: u64, n: usize, k: usize, xs: &mut HashSet<u64>) {
    if s&mask > 0 || xs.contains(&s) {
        return;
    }

    xs.insert(s);
    if s.count_ones() == k as u32 {
        return;
    }

    for i in 0..n*n {
        if s>>i&1 == 1 { continue }
        let u  = if i/n>0 { s>>(i-n)&1 } else { 0 };
        let l = if i%n > 0 { s>>(i-1)&1 } else { 0 };
        let r = if i%n < n-1 { s>>(i+1)&1 } else { 0 };
        let b = if i/n < n-1 { s>>(i+n)&1 } else { 0 };

        if s > 0 && u+l+r+b == 0 {
            continue;
        }
        dfs(s|(1<<i), mask, n, k, xs);
    }
}