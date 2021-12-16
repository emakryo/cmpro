#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeMap, BTreeSet, HashSet};

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
        h: usize,
        w: usize,
        n: usize,
        xs: [(Usize1, Usize1, usize); n],
    }

    let mut ans = vec![0; n];
    let mut ys = BTreeMap::<usize, Vec<_>>::new();
    for (i, (x, y, a)) in xs.into_iter().enumerate() {
        ys.entry(a).or_default().push((x, y, i));
    }

    let mut dpx = vec![-1; h];
    let mut dpy = vec![-1; w];

    for (_, ps) in ys.iter().rev() {
        for &(x, y, i) in ps {
            ans[i] = ans[i].max(dpx[x] + 1);
            ans[i] = ans[i].max(dpy[y] + 1);
        }

        for &(x, y, i) in ps {
            dpx[x] = dpx[x].max(ans[i]);
            dpy[y] = dpy[y].max(ans[i]);
        }
    }


    for a in ans {
        println!("{}", a);
    }
}