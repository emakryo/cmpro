#![allow(unused_macros, unused_imports)]

use std::{collections::{HashMap, HashSet}, hash::Hash};

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
        q: usize,
        mut h: [i64; n],
    }

    let mut g0 = HashMap::new();
    let mut g1 = HashMap::new();
    for i in 0..n-1 {
        if i%2 == 0 {
            *g0.entry(h[i+1]-h[i]).or_insert(0) += 1;
        } else {
            *g1.entry(h[i+1]-h[i]).or_insert(0) += 1;
        }
    }

    let mut f0 = 0;
    let mut f1 = 0;

    for _ in 0..q {
        proconio::input! { t: usize }

        if t == 1 {
            proconio::input! { v: i64 }
            f0 += v;
        } else if t == 2 {
            proconio::input! { v: i64 }
            f1 += v;
        } else {
            proconio::input! { u: Usize1, v: i64 }
            if u%2 == 0 {
                if u > 0 {
                    *g1.get_mut(&(h[u]-h[u-1])).unwrap() -= 1;
                    *g1.entry(h[u]+v-h[u-1]).or_insert(0) += 1;
                }

                if u < n-1 {
                    *g0.get_mut(&(h[u+1]-h[u])).unwrap() -= 1;
                    *g0.entry(h[u+1]-h[u]-v).or_insert(0) += 1;
                }
            } else {
                if u > 0 {
                    *g0.get_mut(&(h[u]-h[u-1])).unwrap() -= 1;
                    *g0.entry(h[u]+v-h[u-1]).or_insert(0) += 1;
                }

                if u < n-1 {
                    *g1.get_mut(&(h[u+1]-h[u])).unwrap() -= 1;
                    *g1.entry(h[u+1]-h[u]-v).or_insert(0) += 1;
                }
            }
            h[u] += v;
        }

        let x0 = *g0.get(&(f0-f1)).unwrap_or(&0);
        let x1 = *g1.get(&(f1-f0)).unwrap_or(&0);

        println!("{}", x0 + x1);
    }
    
}