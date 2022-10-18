#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;
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

    for i in 0..t {
        println!("Case #{}: {}", i+1, if solve() { "YES" } else { "NO" });
    }
}

fn solve() -> bool {
    proconio::input! {
        n: usize,
        k: usize,
        s: [usize; n],
    }

    if 2 * k < n {
        return false;
    }

    let mut c = BTreeMap::new();
    for si in s {
        *c.entry(si).or_default() += 1;
    }

    if 2 < c.values().cloned().max().unwrap() {
        return false;
    }

    true
}
