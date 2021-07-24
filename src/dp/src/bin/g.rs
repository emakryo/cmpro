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
        es: [(Usize1, Usize1); m],
    }

    let mut g = vec![vec![]; n];

    for (x, y) in es {
        g[x].push(y);
    }

    let ord = topsort(&g);
    dbg!(&ord);
    let mut dp = vec![0; n];

    for i in ord {
        for &j in &g[i] {
            dp[j] = dp[j].max(dp[i]+1);
        }
    }

    println!("{}", dp.iter().max().unwrap());
}

fn topsort(g: &Vec<Vec<usize>>) -> Vec<usize> {
    let n = g.len();
    let mut ord = vec![];

    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    enum S {
        Unseen,
        Visit,
        Done,
    }
    let mut state = vec![S::Unseen; n];

    fn rec(u: usize, g: &Vec<Vec<usize>>, state: &mut Vec<S>, ord: &mut Vec<usize>) -> bool {
        if state[u] == S::Visit { return true; }
        if state[u] == S::Done { return false; }
        
        state[u] = S::Visit;
        for &v in &g[u] {
            if rec(v, g, state, ord) { return true; }
        }
        ord.push(u);
        state[u] = S::Done;
        false
    }

    for i in 0..n {
        if state[i] == S::Done { continue }
        if rec(i, g, &mut state, &mut ord) {
            return vec![];
        }
    }

    ord.reverse();

    return ord;
}