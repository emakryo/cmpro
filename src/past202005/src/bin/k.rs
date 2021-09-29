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
        q: usize,
        qs: [(Usize1, Usize1, Usize1); q],
    }

    let mut below = vec![n; n];
    let mut top = (0..n).collect::<Vec<_>>();

    for (f, t, x) in qs {
        let y = top[t];
        top[t] = top[f];
        top[f] = below[x];
        below[x] = y;
    }

    let mut ans = vec![0; n];
    for i in 0..n {
        let mut x = top[i];
        while x != n {
            ans[x] = i+1;
            x = below[x];
        }
    }

    for i in 0..n {
        println!("{}", ans[i]);
    }

}