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
        a: [i64; n],
        es: [(Usize1, Usize1, i64); m],
    }

    let mut g = vec![vec![]; n];
    for (u, v, t) in es {
        g[u].push((v, t));
        g[v].push((u, t));
    }

    let mut dist = vec![1e18 as i64; n];
    let mut que = BinaryHeap::new();
    que.push((-0i64, 0));
    dist[0] = 0;
    
    while let Some((d, u)) = que.pop() {
        let d = -d;
        if d > dist[u]{ continue }
        for &(v, t) in &g[u] {
            if dist[u] + t < dist[v] {
                dist[v] = dist[u] + t;
                que.push((-dist[v], v));
            }
        }
    }

    let mut dp = vec![0; n];
    let mut que = BinaryHeap::new();
    dp[n-1] = a[n-1];
    que.push((dist[n-1], n-1));

    while let Some((_, u)) = que.pop() {
        for &(v, t) in &g[u] {
            if dist[u] != dist[v] + t { continue }
            if dp[v] < dp[u] + a[v] {
                dp[v] = dp[u] + a[v];
                que.push((dist[v], v));
            }
        }
    }

    println!("{}", dp[0]);
}