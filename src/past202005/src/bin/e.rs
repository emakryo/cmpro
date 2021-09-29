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
        m: usize,
        q: usize,
        es: [(Usize1, Usize1); m],
        mut c: [usize; n],
    }

    let mut g = vec![vec![]; n];

    for (u, v) in es {
        g[u].push(v);
        g[v].push(u);
    }

    for _ in 0..q {
        proconio::input! { t: usize }
        if t == 1 {
            proconio::input! { x: Usize1 }
            println!("{}", c[x]);
            for &v in &g[x] {
                c[v] = c[x];
            }
        } else {
            proconio::input! { x: Usize1, y: usize }
            println!("{}", c[x]);
            c[x] = y;
        }
    }
}