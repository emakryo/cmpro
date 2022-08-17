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
        n: usize,
        xs: [(String, usize); n],
    }

    let mut seen = HashSet::new();
    let mut ans_val = 0;
    let mut ans_idx = 0;
    for (i, (s, t)) in xs.into_iter().enumerate() {
        if seen.contains(&s) {
            continue;
        }

        seen.insert(s);
        if ans_val < t {
            ans_idx = i + 1;
            ans_val = t;
        }
    }

    println!("{}", ans_idx);

}