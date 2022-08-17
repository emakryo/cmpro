#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;

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
        t: usize
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        s: Bytes,
    }

    let cs = b"AEIOU";
    let vs = b"BCDFGHJKLMNPQRSTVWXYZ";
    let mut xs = BTreeMap::new();
    for c in s {
        *xs.entry(c).or_insert(0) += 1;
    }

    let nc = cs.iter().map(|x| xs.get(x).unwrap_or(&0)).sum::<i32>();
    let nv = vs.iter().map(|x| xs.get(x).unwrap_or(&0)).sum::<i32>();

    let mut ans = i32::max_value();

    for c in cs {
        ans = ans.min(2*(nc-xs.get(c).unwrap_or(&0)) + nv);
    }
    for c in vs {
        ans = ans.min(2*(nv-xs.get(c).unwrap_or(&0)) + nc);
    }

    println!("{}", ans);
}