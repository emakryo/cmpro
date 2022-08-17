#![allow(unused_macros, unused_imports)]

use proconio::marker::{Bytes, Chars};
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
        t: usize,
    }
    for i in 0..t {
        print!("Case #{}:", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        s: Bytes,
        k: usize,
        xs: [Bytes; k],
    }

    let s = s.iter().map(|x| (x-b'A') as usize).collect::<Vec<_>>();
    let m = 26;

    let mut d = vec![vec![1000; m]; m];
    for xi in xs {
        let a = (xi[0] - b'A') as usize;
        let b = (xi[1] - b'A') as usize;
        d[a][b] = 1;
    }

    for k in 0..m {
        for i in 0..m {
            for j in 0..m {
                d[i][j] = d[i][j].min(d[i][k]+d[k][j]);
            }
        }
    }

    let mut ans = i32::max_value();
    for k in 0..m {
        let mut x = 0;
        let mut ok = true;
        for &c in &s {
            if c!=k {
                if d[c][k] < 1000 {
                    x += d[c][k];
                } else {
                    ok = false;
                }
            }
        }
        if ok {
            ans = ans.min(x);
        }
    }

    if ans < i32::max_value() {
        println!("{}", ans);
    } else {
        println!("-1");
    }
}