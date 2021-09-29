#![allow(unused_macros, unused_imports)]

use proconio::marker::Usize1;
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        es: [(Usize1, Usize1); m],
        q: usize,
        qs: [(Usize1, usize); q],
    }

    let lim = 450;
    let mut g = vec![vec![]; n];
    for (a, b) in es{
        g[a].push(b);
        g[b].push(a);
    }
    let mut h = vec![vec![]; n]; // 各頂点から高次数(>lim)な頂点へ向かう辺
    for i in 0..n {
        for &v in &g[i] {
            if g[v].len() > lim {
                h[i].push(v);
            }
        }
    }

    let mut c = vec![1];
    for &(_, y) in &qs {
        c.push(y);
    }
    let mut t = vec![0; n];
    let mut s = vec![0; n];

    for (i, (x, _)) in qs.into_iter().enumerate() {
        let mut y = t[x].max(s[x]);
        if g[x].len() <= lim {
            for &v in &g[x] {
                y = y.max(t[v]);
            }
        }

        println!("{}", c[y]);

        t[x] = i+1;
        for &v in &h[x] {
            s[v] = i+1;
        }

        // dbg!(&c, &t);
    }
}