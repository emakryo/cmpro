#![allow(unused_macros, unused_imports)]

use std::{collections::BinaryHeap, cmp::Reverse};

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
        x: [i64; n],
        es: [(Usize1, Usize1); n-1],
        qs: [(Usize1, Usize1); q],
    }

    let mut g = vec![vec![]; n];
    for &(a, b) in &es {
        g[a].push(b);
        g[b].push(a);
    }
    let mut pqs = vec![BinaryHeap::<Reverse<i64>>::new(); n];

    fn dfs(v: usize, p: Option<usize>, x: &Vec<i64>, g: &Vec<Vec<usize>>, pqs: &mut Vec<BinaryHeap<Reverse<i64>>>) {
        pqs[v].push(Reverse(x[v]));

        for &u in &g[v] {
            if Some(u) == p { continue }
            dfs(u, Some(v), x, g, pqs);
        }

        let pq = pqs[v].clone();
        if let Some(p) = p {
            for z in pq {
                pqs[p].push(z);
                if pqs[p].len() > 20 {
                    pqs[p].pop();
                }
            }
        }
    }

    dfs(0, None, &x, &g, &mut pqs);
    let pqs = pqs.into_iter().map(|pq| pq.into_sorted_vec()).collect::<Vec<_>>();
    for (v, k) in qs {
        println!("{}", pqs[v][k].0);
    }

}
