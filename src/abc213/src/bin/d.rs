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

fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>, ans: &mut Vec<usize>) {
    ans.push(u+1);
    for &v in &g[u] {
        if v == p { continue }
        dfs(v, u,  g, ans);
        ans.push(u+1);
    }
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(Usize1, Usize1); n-1],
    }

    let mut g = vec![vec![]; n];
    for (a, b) in xs {
        g[a].push(b);
        g[b].push(a);
    }
    for gi in &mut g {
        gi.sort();
    }

    let mut ans = vec![];
    dfs(0, usize::max_value(), &g, &mut ans);

    println!("{}", ans.iter().map(ToString::to_string).collect::<Vec<_>>().join(" "));
}