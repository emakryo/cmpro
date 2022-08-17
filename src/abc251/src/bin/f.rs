#![allow(unused_macros, unused_imports)]

use std::f32::consts::E;

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
    }

    let mut g = vec![vec![]; n];
    for (u, v) in es {
        g[u].push(v);
        g[v].push(u);
    }

    fn dfs(u: usize, visit: &mut [bool], g: &Vec<Vec<usize>>, ans: &mut Vec<(usize, usize)>) {
        for &v in &g[u] {
            if visit[v] {
                continue;
            }

            ans.push((u+1, v+1));
            visit[v] = true;
            dfs(v, visit, g, ans);
        }
    }

    let mut t1 = vec![];
    let mut visit = vec![false; n];
    visit[0] = true;
    dfs(0, &mut visit, &g, &mut t1);

    dbg!(&t1);
    assert_eq!(t1.len(), n-1);
    for (u, v) in t1 {
        println!("{} {}", u, v);
    }

    fn bfs(s: usize, visit: &mut [bool], g: &Vec<Vec<usize>>, ans: &mut Vec<(usize, usize)>) {
        let mut xs = vec![s];

        while xs.len() > 0 {
            let mut ys = vec![];

            for u in xs {
                for &v in &g[u] {
                    if visit[v] { 
                        continue;
                    }

                    ys.push(v);
                    visit[v] = true;
                    ans.push((u+1, v+1));
                }
            }

            ys.sort();
            ys.dedup();

            xs = ys;
        }
    }

    let mut t2 = vec![];
    let mut visit = vec![false; n];
    visit[0] = true;
    bfs(0, &mut visit, &g, &mut t2);

    assert_eq!(t2.len(), n-1);
    for (u, v) in t2 {
        println!("{} {}", u, v);
    }
}