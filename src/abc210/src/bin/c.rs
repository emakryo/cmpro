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
        c: [usize; n],
    }

    let mut cnt = HashMap::new();

    for i in 0..k {
        *cnt.entry(c[i]).or_insert(0) += 1;
    }
    let mut ans = cnt.len();

    for i in k..n {
        *cnt.entry(c[i]).or_insert(0) += 1;
        if *cnt.get(&c[i-k]).unwrap() == 1 {
            cnt.remove_entry(&c[i-k]);
        } else {
            *cnt.get_mut(&c[i-k]).unwrap() -= 1;
        }
        ans = ans.max(cnt.len());
    }

    println!("{}", ans);
}