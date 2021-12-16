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

    fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>, dp: &mut Vec<(usize, bool)>) {
        let mut matched = false;
        for &v in &g[u] {
            if v == p { continue; }
            dfs(v, u, g, dp);
            dp[u].0 += dp[v].0;
            if !dp[v].1 {
                matched = true;
            }
        }

        dp[u].1 = matched;
        if matched {
            dp[u].0 += 1;
        }
    }

    fn dfs2(u: usize, p: usize, g: &Vec<Vec<usize>>, dp: &Vec<(usize, bool)>, s: (usize, bool), total: usize) -> usize {
        let mut m = s.0;
        let mut xs = vec![];
        if !s.1 {
            xs.push(p);
        }

        for &v in &g[u] {
            if v == p { continue; }
            m += dp[v].0;
            if !dp[v].1 {
                xs.push(v);
            }
        }

        let mut ret = 0;
        if m == total {
            ret += 1;
        }

        for &v in &g[u] {
            if v == p { continue; }
            let mut t = (m-dp[v].0, false);
            if xs.len() > 1 || (xs.len() == 1 && xs[0] != v) {
                t.0 += 1;
                t.1 = true;
            }
            ret += dfs2(v, u, g, dp, t, total);
        }

        ret
    }

    let mut dp = vec![(0, false); n];
    dfs(0, usize::max_value(), &g, &mut dp);
    let ans = dfs2(0, usize::max_value(), &g, &dp, (0, true), dp[0].0);
    println!("{}", ans);
}