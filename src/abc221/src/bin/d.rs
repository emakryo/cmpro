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
        n: usize,
        xs: [(usize, usize); n]
    }

    let mut m = BTreeMap::new();

    for (a, b) in xs {
        *m.entry(a).or_insert(0i32) += 1;
        *m.entry(a+b).or_insert(0) -= 1;
    }

    let m = m.into_iter().collect::<Vec<_>>();

    let mut ans = vec![0; n+1];
    let mut x = 0;
    for i in 0..m.len()-1 {
        x += m[i].1;
        ans[x as usize] += m[i+1].0 - m[i].0;
    }

    println!("{}", ans.iter().skip(1).map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}