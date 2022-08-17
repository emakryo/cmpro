#![allow(unused_macros, unused_imports)]

use std::collections::{VecDeque, BTreeMap};

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

pub fn dijkstra(s: usize, g: &Vec<Vec<(usize, i64)>>) -> Vec<i64> {
    let n = g.len();

    let inf = i64::max_value();
    let mut dist = vec![inf; n];
    dist[s] = 0;
    let mut que = std::collections::BinaryHeap::new();
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

    dist
}
fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        es: [(Usize1, Usize1, i64); m],
    }

    let mut g = vec![vec![]; n];

    for &(a, b, c) in &es {
        g[a].push((b, c));
        g[b].push((a, c));
    }

    let mut idx = BTreeMap::new();
    for (i, &(a, b, _)) in es.iter().enumerate() {
        idx.insert((a, b), i+1);
        idx.insert((b, a), i+1);
    }

    let dist = dijkstra(0, &g);

    let mut ans = vec![];
    let mut visit = vec![false; n];
    let mut que = VecDeque::new();
    que.push_back(0);
    visit[0] = true;

    while let Some(u) = que.pop_front() {
        for &(v, c) in &g[u] {
            if visit[v] {
                continue;
            }

            if dist[u] + c == dist[v] {
                ans.push(idx.get(&(u, v)).or(idx.get(&(v, u))).unwrap());
                que.push_back(v);
                visit[v] = true;
            }
        }
    }

    println!("{}", ans.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}
