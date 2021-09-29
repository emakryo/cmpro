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
    for (x, y) in es {
        g[x].push(y);
        g[y].push(x);
    }

    fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>) -> usize {
        let mut r = 0;
        for &v in &g[u] {
            if v == p { continue }
            r ^= 1 + dfs(v, u, g);
        }

        r
    }

    if dfs(0, usize::max_value(), &g) == 0 {
        println!("Bob");
    } else {
        println!("Alice");
    }
}