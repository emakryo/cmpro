#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;

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

    let f = |mut que: Vec<(usize, usize)>| {
        let mut leaf = que.len();
        let mut depth = 0;
        while que.len() > 0 {
            let mut next = vec![];
            let mut cmax = 1;
            for (u, p) in que {
                let mut k = 0;
                for &v in &g[u] {
                    if v == p { continue; }
                    next.push((v, u));
                    k += 1;
                }
                cmax = cmax.max(k);
            }
            depth += 1;
            que = next;
            leaf *= cmax;
        }

        (depth, leaf)
    };

    let mut ans = (usize::max_value(), usize::max_value());
    for i in 0..n {
        ans = ans.min(f(vec![(i, usize::max_value())]));
    }

    for i in 0..n {
        for j in i+1..n {
            ans = ans.min(f(vec![(i, j), (j, i)]));
        }
    }

    println!("{} {}", ans.0, ans.1);
}