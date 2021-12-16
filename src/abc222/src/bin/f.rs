#![allow(unused_macros, unused_imports)]

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
        es: [(Usize1, Usize1, u64); n-1],
        d: [u64; n],
    }

    let mut g = vec![vec![]; n];
    for (a, b, c) in es {
        g[a].push((b, c));
        g[b].push((a, c));
    }

    let mut mcost = vec![0; n];
    fn dfs(u: usize, p: usize, g: &Vec<Vec<(usize, u64)>>, d: &Vec<u64>, mcost: &mut Vec<u64>) {
        mcost[u] = d[u];
        for &(v, c) in &g[u] {
            if v == p { continue; }
            dfs(v, u, g, d, mcost);

            mcost[u] = mcost[u].max(c + mcost[v]);
        }
    }

    dfs(0, usize::max_value(), &g, &d, &mut mcost);
    let mut ans = vec![0; n];

    fn dfs2(u: usize, p: usize, x: u64, g: &Vec<Vec<(usize, u64)>>, d: &Vec<u64>, mcost: &Vec<u64>, ans: &mut Vec<u64>){
        ans[u] = x;

        let mut lm = vec![0u64];
        let mut rm = vec![0u64];
        let mut cp = 0;
        for &(v, c) in &g[u] {
            if v == p {
                cp = c;
                continue;
            }
            lm.push(*lm.last().unwrap().max(&(mcost[v]+c)));
        }
        for &(v, c) in g[u].iter().rev() {
            if v == p { continue; }
            rm.push(*rm.last().unwrap().max(&(mcost[v]+c)));
        }
        rm.reverse();

        let mut j = 0;
        for &(v, c) in &g[u] {
            if v == p { continue; }
            ans[u] = ans[u].max(mcost[v]+c);
            dbg!(u, v, x, cp, lm[j], rm[j+1]);
            let y = c + d[u].max(x).max(lm[j]).max(rm[j+1]);
            j += 1;

            dfs2(v, u, y, g, d, mcost, ans);
        }
    }
    dbg!(&mcost);

    dfs2(0, usize::max_value(), 0, &g, &d, &mcost, &mut ans);

    for a in ans {
        println!("{}", a);
    }
}