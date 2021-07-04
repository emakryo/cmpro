#![allow(unused_imports)]

use std::collections::VecDeque;
use proconio::marker::Usize1;

#[proconio::fastout]
fn main() {
    proconio::input! {
        n: usize,
        xs: [(Usize1, Usize1); n],
    }

    let mut g = vec![vec![]; n];
    let mut visit = vec![false; n];
    let mut que = VecDeque::new();
    let mut ans = vec![];

    for (i, (a, b)) in xs.iter().enumerate() {
        g[*a].push(i);
        g[*b].push(i);
        if i==*a || i==*b {
            que.push_back(i);
            ans.push(i);
            visit[i] = true;
        }
    }

    while let Some(u) = que.pop_front() {
        for &v in &g[u] {
            if !visit[v] {
                visit[v] = true;
                ans.push(v);
                que.push_back(v);
            }
        }
    }

    if ans.len() < n {
        println!("-1");
    } else {
        for a in ans.iter().rev() {
            println!("{}", a+1);
        }
    }
}