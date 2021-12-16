#![allow(unused_macros, unused_imports)]

use proconio::marker::Bytes;
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
        n: Bytes,
    }

    let m = n.len();
    let mut cs = n.into_iter().map(|c| (c - b'0') as u64).collect::<Vec<_>>();
    cs.sort();
    cs.reverse();

    let mut a = 0;
    let mut b = 0;

    for i in 0..m/2 {
        let c = cs[2*i];
        let d = cs[2*i+1];
        // d <= c

        if a <= b {
            a = 10*a + c;
            b = 10*b + d;
        } else {
            a = 10*a + d;
            b = 10*b + c;
        }
    }

    if m%2==1 {
        if a <= b {
            a = 10*a + cs[m-1];
        } else {
            b = 10*b + cs[m-1];
        }
    }

    println!("{}", a*b);
}