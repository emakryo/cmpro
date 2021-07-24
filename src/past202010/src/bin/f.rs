#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;
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
        s: [String; n],
    }

    let mut m = HashMap::new();
    for si in s {
        *m.entry(si).or_insert(0) += 1;
    }

    let mut xs: Vec<_> = m.into_iter().map(|(s, x)| (x, s)).collect();
    xs.sort(); xs.reverse();

    dbg!(&xs);
    if k > 1 && xs[k-2].0 == xs[k-1].0 || k < xs.len() && xs[k].0 == xs[k-1].0 {
        println!("AMBIGUOUS");
    } else {
        println!("{}", xs[k-1].1);
    }
}