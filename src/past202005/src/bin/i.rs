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
    }

    let mut x = (0..n).collect::<Vec<_>>();
    let mut y = (0..n).collect::<Vec<_>>();
    let mut tr = false;

    for _ in 0..q {
        proconio::input! { t: usize }
        if t == 1 {
            proconio::input! { a: Usize1, b: Usize1 }
            if tr {
                y.swap(a, b);
            } else {
                x.swap(a, b);
            }
        } else if t == 2 {
            proconio::input! { a: Usize1, b: Usize1 }
            if tr {
                x.swap(a, b);
            } else {
                y.swap(a, b);
            }
        } else if t == 3 {
            tr = !tr;
        } else {
            proconio::input! { a: Usize1, b: Usize1 }
            if tr {
                println!("{}", x[b] * n + y[a]);
            } else {
                println!("{}", x[a] * n + y[b]);
            }
        }
    }
}