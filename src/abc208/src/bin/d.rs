#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}
use std::collections::BinaryHeap;

use proconio::marker::*;

fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        es: [(Usize1, Usize1, usize); m],
    }

    let inf = 1000000000;
    let mut dist = vec![vec![inf; n]; n];
    for i in 0..n {
        dist[i][i] = 0;
    }

    let mut g = vec![vec![]; n];
    let mut rg = vec![vec![]; n];
    for (a, b, c) in es {
        g[a].push((b, c));
        rg[b].push((a, c));
        dist[a][b] = c;
    }

    let mut ans = 0;
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                dist[i][j] = dist[i][j].min(dist[i][k]+ dist[k][j]);
            }
        }

        for i in 0..n {
            for j in 0..n {
                if dist[i][j] < inf {
                    ans += dist[i][j];
                }
            }
        }
    }

    println!("{}", ans);


    // let mut ans = 0;
    // for k in 0..n {
    //     for s in 0..n {
    //         let mut que = BinaryHeap::new();
    //         for &(u , c) in &rg[k] {
    //             if dist[s][u] < inf && dist[s][u] + c < dist[s][k] {
    //                 dist[s][k] = dist[s][u] + c;
    //             }
    //         }
    //         que.push((-(dist[s][k] as i64), k));

    //         while let Some((d, u)) = que.pop() {
    //             let d = (-d) as usize;
    //             if d > dist[s][u] { continue }
    //             for &(v, c) in &g[u] {
    //                 let nd = dist[s][u] + c;
    //                 if nd < dist[s][v] {
    //                     if v <= k {
    //                         que.push((-(nd as i64), v));
    //                     }
    //                     dist[s][v] = nd;
    //                 }
    //             }
    //         }

    //         for i in 0..n {
    //             if dist[s][i] < inf {
    //                 ans += dist[s][i];
    //             }
    //         }
    //         dbg!(k, s, &dist[s]);
    //     }
    // }

    // println!("{}", ans);
}