#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeMap, HashMap};

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
        xs: [(Usize1, Usize1, i64, i64); m],
        qs: [(i64, Usize1, i64); q],
    }

    let mut g = vec![(0, 0); m]; // (next, time)

    let mut c = vec![vec![]; n]; // town -> [(end, bus)]

    for (i, &(a, _, s, _)) in xs.iter().enumerate() {
        c[a].push((s, i));
    }

    let mut d = BTreeMap::new();
    let mut f = HashMap::new();

    for (j, ci) in c.iter_mut().enumerate() {
        ci.sort();

        for (s, i) in ci {
            let k = g.len();
            g.push((*i, *s));
            d.insert((j, *s), k);
            f.insert(k, j);
            // println!("{} {} {} {}", j, k, *i, *s);
        }

        let k = g.len();
        g.push((k, i64::max_value()));
        d.insert((j, i64::max_value()), k);
        f.insert(k, j);
        // println!("{} {} {} {}", j, k, k, i64::max_value());
    }

    for (i, &(_, b, _, t)) in xs.iter().enumerate() {
        let (_, &k) = d.range((b, t)..(usize::max_value(), 0)).next().unwrap();
        g[i] = (k, t);
    }

    let p = 20;
    let mut db = vec![vec![0; p]; g.len()];
    let mut visit = vec![false; g.len()];

    for i in 0..g.len() {
        if !visit[i] {
            dfs(i, &g, &mut visit, &mut db);
        }
    }

    dbg!(&g);
    // dbg!(&db);

    for (s, x, t) in qs {
        let (_,  &x) = d.range((x, s)..(usize::max_value(), 0)).next().unwrap();
        let mut x = x;

        // dbg!(t);
        while g[x].1 < t {
            let mut k = 0;
            while g[db[x][k+1]].1 < t {
                // dbg!(x, k+1, db[x][k+1], g[db[x][k+1]]);
                k += 1;
            }
            x = db[x][k];
        }

        // dbg!(x);
        if x < m {
            println!("{} {}", xs[x].0+1, xs[x].1+1);
        } else {
            println!("{}", f.get(&x).unwrap()+1);
        }
    }
}

fn dfs(u: usize, g: &Vec<(usize, i64)>, visit: &mut Vec<bool>, db: &mut Vec<Vec<usize>>) {
    if g[u].0 != u && !visit[g[u].0] {
        dfs(g[u].0, g, visit, db);
    }

    visit[u] = true;
    let p = db[0].len();

    db[u][0] = g[u].0;
    for i in 1..p {
        db[u][i] = db[db[u][i-1]][i-1];
    }
}