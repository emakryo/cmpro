#![allow(unused_macros, unused_imports)]

use std::collections::{BinaryHeap, VecDeque};

use proconio::marker::{Chars, Usize1};
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
        x: [i64; 3],
        s: Chars,
        es: [(Usize1, Usize1, i64); m],
    }

    let mut g = vec![vec![]; n+6];

    for (a, b, c) in es {
        g[a].push((b, c));
        g[b].push((a, c));
    }

    for i in 0..n {
        match s[i] {
            'A' => {
                g[i].push((n, 0));
                g[n+3].push((i, 0));
            }
            'B' => {
                g[i].push((n+1, 0));
                g[n+4].push((i, 0));
            }
            'C' => {
                g[i].push((n+2, 0));
                g[n+5].push((i, 0));
            }
            _ => panic!(),
        }
    }

    g[n].push((n+4, x[0])); // A->B
    g[n].push((n+5, x[1])); // A->C
    g[n+1].push((n+3, x[0])); // B->A
    g[n+1].push((n+5, x[2])); // B->C
    g[n+2].push((n+3, x[1])); // C->A
    g[n+2].push((n+4, x[2])); // C->B

    let ans = dijkstra(0, n-1, &g);
    println!("{}", ans);
}

fn dijkstra(s: usize, t: usize, g: &Vec<Vec<(usize, i64)>>) -> i64 {
    let n = g.len();

    let inf = i64::max_value();
    let mut dist = vec![inf; n];
    dist[s] = 0;
    let mut que = BinaryHeap::new();
    que.push((0, s));

    while let Some((d, u)) = que.pop() {
        let d = -d;
        if d > dist[u] {
            continue;
        }
        for &(v, w) in &g[u] {
            let d = d + w;
            if d < dist[v] {
                dist[v] = d;
                que.push((-d, v));
            }
        }
    }

    dist[t]
}