#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

use std::collections::BinaryHeap;

use proconio::marker::Usize1;

fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        q: usize,
        es: [(Usize1, Usize1, i64); m],
        x: [i64; q],
    }

    let mut g = vec![vec![]; n];
    for (a, b, c) in es {
        g[a].push((b, c));
        g[b].push((a, c));
    }

    let mut count = 1;
    let mut visit = vec![false; n];
    let mut que = BinaryHeap::new();
    visit[0] = true;
    for &(v, c) in &g[0] {
        que.push((-c, v));
    }


    for i in 0..q {
        let mut next = vec![];
        while let Some(&(c, v)) = que.peek().clone() {
            // dbg!(i, -c, v);
            if visit[v] {
                que.pop();
                continue;
            }
            if -c > x[i] { break }
            count += 1;
            que.pop();
            visit[v] = true;
            next.push(v);
        }

        for v in next {
            for &(u, d) in &g[v] {
                if !visit[u] {
                    que.push((-d, u));
                }
            }
        }

        println!("{}", count);
    }
}