#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeSet, HashSet};

use proconio::marker::Usize1;
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
        m: usize,
        xs: [(Usize1, Usize1); m],
    }

    let mut g = vec![HashSet::new(); n];
    let mut rg = vec![HashSet::new(); n];

    for (a, b) in xs {
        g[a].insert(b);
        rg[b].insert(a);
    }

    let mut x = BTreeSet::new();
    for i in 0..n {
        if rg[i].len() == 0 {
            x.insert(i);
        }
    }

    let mut done = vec![false; n];
    let mut ans = vec![];
    for _ in 0..n {
        if x.len() == 0 {
            println!("-1");
            return;
        }

        let v = loop {
            let v = *x.iter().next().unwrap();
            x.remove(&v);
            if !done[v] {
                done[v] = true;
                break v;
            }
        };

        for &u in &g[v] {
            if done[u] { continue; }
            rg[u].remove(&v);
            if rg[u].len() == 0 {
                x.insert(u);
            }
        }
        ans.push(v+1);

        dbg!(&ans, &x);
    }

    println!("{}", ans.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}