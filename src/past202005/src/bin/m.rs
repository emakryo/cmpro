#![allow(unused_macros, unused_imports)]

use std::collections::BinaryHeap;

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
        es: [(Usize1, Usize1); m],
        s: Usize1,
        k: usize,
        mut t: [Usize1; k],
    }

    let inf = 10i64.pow(9);
    let k = k+1;
    t.push(s);

    let mut dist = vec![vec![inf; k]; k];
    let mut g= vec![vec![]; n];
    for (a, b) in es {
        g[a].push(b);
        g[b].push(a);
    }

    for (i, &ti) in t.iter().enumerate() {
        let mut tdist = vec![inf; n];
        let mut que = BinaryHeap::new();
        tdist[ti] = 0;
        que.push((0, ti));

        while let Some((d, u)) = que.pop() {
            let d = -d;
            if d < tdist[u] {
                continue;
            }

            for &v in &g[u] {
                let dv = tdist[u] + 1;
                if dv < tdist[v] {
                    tdist[v] = dv;
                    que.push((-dv, v));
                }
            }
        }

        for j in 0..k {
            dist[i][j] = tdist[t[j]];
        }
    }

    let mut dp = vec![vec![inf; k]; 1<<k];
    dp[1<<(k-1)][k-1] = 0;

    for s in 1<<(k-1)..1<<k {
        for i in 0..k {
            if dp[s][i] == inf {
                continue;
            }
            
            for j in 0..k {
                if s>>j&1 == 1 {
                    continue;
                }
                dp[s|1<<j][j] = dp[s|1<<j][j].min(dp[s][i] + dist[i][j]);
            }
        }
    }

    println!("{}", dp[(1<<k)-1].iter().min().unwrap());
}