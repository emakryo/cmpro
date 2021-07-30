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
        a: [usize; n],
        mut b: [usize; n],
    }

    b.sort();

    let mut xs = HashMap::new();
    for &ai in &a {
        for &bi in &b {
            *xs.entry(ai^bi).or_insert(0) += 1;
        }
    }

    let mut ans = vec![];
    for (x, m) in xs {
        if m < n { continue; }

        let mut c: Vec<_> = a.iter().map(|&ai| ai^x).collect();
        c.sort();

        if b == c {
            ans.push(x);
        }
        
    }

    ans.sort();
    println!("{}", ans.len());
    for a in ans {
        println!("{}", a);
    }
}