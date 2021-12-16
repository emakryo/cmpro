#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeMap, HashSet};
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
        ps: [(i64, i64); n],
    }

    let s = ps.iter().cloned().collect::<HashSet<(i64, i64)>>();

    let mut ans = 0;
    for i in 0..n {
        for j in i+1..n {
            if ps[i].0 == ps[j].0 || ps[i].1 == ps[j].1 {
                continue;
            }
            if s.contains(&(ps[i].0, ps[j].1)) && s.contains(&(ps[j].0, ps[i].1)) {
                ans += 1;
            }
        }
    }

    println!("{}", ans / 2);
}