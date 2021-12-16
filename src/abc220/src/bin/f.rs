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
        es: [(Usize1, Usize1); n-1],
    }

    let mut g = vec![vec![]; n];

    for (a, b) in es {
        g[a].push(b);
        g[b].push(a);
    }

    let mut size = vec![0; n];
    let mut dp = vec![0; n];

    fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>, size: &mut Vec<usize>, dp: &mut Vec<u64>) {
        size[u] = 1;
        for &v in &g[u] {
            if v == p { continue; }
            dfs(v, u, g, size, dp);
            size[u] += size[v];
            dp[u] += dp[v] + size[v] as u64;
        }
    }

    dfs(0, usize::max_value(), &g, &mut size, &mut dp);

    fn dfs2(u: usize, p: usize, px: u64, g: &Vec<Vec<usize>>, size: &Vec<usize>, dp: &Vec<u64>, ans: &mut Vec<u64>) {
        let n = g.len();
        ans[u] = dp[u] + px + (n - size[u]) as u64;
        for &v in &g[u] {
            if v == p { continue; }
            dfs2(v, u, ans[u] - dp[v] - size[v] as u64, g, size, dp, ans);
        }
    }

    let mut ans = vec![0; n];
    dfs2(0, usize::max_value(), 0, &g, &size, &dp, &mut ans);

    for a in ans {
        println!("{}", a);
    }
}