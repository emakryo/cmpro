#![allow(unused_macros, unused_imports)]

use std::collections::{HashMap, VecDeque};

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
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        es: [(Usize1, Usize1); n-1],
        f: [usize; n],
    }

    let mut g = vec![vec![]; n];

    for (a, b) in es {
        g[a].push(b);
        g[b].push(a);
    }

    let mut call = HashMap::new();
    for &fi in &f {
        *call.entry(fi).or_insert(0) += 1;
    }

    let mut que = VecDeque::new();
    let mut ord = vec![];
    let mut par = vec![0; n];
    let mut visit = vec![false; n];
    que.push_back(0);
    visit[0] = true;
    ord.push(0);

    while let Some(u) = que.pop_front() {
        for &v in &g[u] {
            if visit[v] { continue }
            que.push_back(v);
            ord.push(v);
            visit[v] = true;
            par[v] = u;
        }
    }


    let mut size = vec![0; n];

    for &u in ord.iter().rev() {
        for &v in &g[u] {
            if v == par[u] { 
                continue;
            }

            size[u] += size[v];
        }
        size[u] += 1;
    }

    for gi in &mut g {
        gi.sort_by_key(|u| -size[*u]);
    }

    let mut dp = vec![0; n];
    let mut cs: Vec<Option<HashMap<usize, i32>>> = vec![None; n];

    for &u in ord.iter().rev() {
        let mut c: Option<HashMap<usize, i32>> = None;
        for &v in &g[u] {
            if v == par[u] { continue }
            // let (r, cv) = dfs(v, u, call, f, g);

            dp[u] += dp[v];
            let cv = cs[v].take().unwrap();
            if cv.len() == 0 {
                dp[u] += 1;
            }
            // dbg!(v+1, &cv, ret);
            if let Some(c) = &mut c {
                for (fv, n) in cv {
                    let x = c.entry(fv).or_insert(0);
                    *x += n;
                    if *x == *call.get(&fv).unwrap() {
                        c.remove(&fv);
                    }
                }
            } else {
                c = Some(cv);
            }
        }

        let mut c = if let Some(mut c) = c {
            let x = c.entry(f[u]).or_insert(0);
            *x += 1;
            c
        } else {
            vec![(f[u], 1)].into_iter().collect::<HashMap<_, _>>()
        };

        let x = c.entry(f[u]).or_insert(0);
        if *x == *call.get(&f[u]).unwrap() {
            c.remove(&f[u]);
        }
        cs[u] = Some(c);
    }

    println!("{}", dp[0]);
}