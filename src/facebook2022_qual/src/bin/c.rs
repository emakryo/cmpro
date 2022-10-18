#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;

use proconio::marker::Chars;
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
        println!("Case #{}:", i+1);
        solve();
    }

}

fn solve() {
    proconio::input! {
        n: usize,
        c0: String,
    }
    let mut ans = vec![];

    let m = 10;
    for i in 0..1<<m {
        let mut s = String::new();
        for k in 0..m {
            if (i>>k)&1 == 1 {
                s.push('-');
            } else {
                s.push('.');
            }
        }

        if c0.starts_with(&s) || s.starts_with(&c0) {
            continue;
        }

        println!("{}", &s);
        ans.push(s);
         if ans.len() == n - 1 {
            break;
        }
    }
}
