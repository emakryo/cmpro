#![allow(unused_macros, unused_imports)]

use std::collections::{HashMap, HashSet, VecDeque};

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
        m: usize,
        es: [(Usize1, Usize1); m],
        p: [Usize1; 8],
    }

    let mut x0 = vec![0; 9];
    for i in 0..8 {
        x0[p[i]] = i+1;
    }

    let mut a = vec![vec![]; 9];
    for (u, v) in es {
        a[u].push(v);
        a[v].push(u);
    }

    let g = vec![1, 2, 3, 4, 5, 6, 7, 8, 0];
    let mut visit = HashMap::new();
    visit.insert(x0.clone(), 0);
    let mut que = VecDeque::new();
    que.push_back(x0);

    while let Some(mut x) = que.pop_front() {
        let d = *visit.get(&x).unwrap();
        // dbg!(&x, d);
        let mut k = 0;
        for i in 0..9 {
            if x[i] == 0 {
                k = i;
            }
        }

        for &v in &a[k] {
            x.swap(k, v);
            if !visit.contains_key(&x) {
                que.push_back(x.clone());
                visit.insert(x.clone(), d+1);
            }
            x.swap(k, v);
        }
    }

    if let Some(ans) = visit.get(&g) {
        println!("{}", ans);
    } else {
        println!("-1");
    }
}