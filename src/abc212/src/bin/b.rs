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
        mut x: Bytes,
    }

    for x in &mut x {
        *x -= b'0';
    }

    let ans = if x[0] == x[1] && x[1] == x[2] && x[2] == x[3] {
        "Weak"
    } else if x[1] == (x[0]+1)%10 && x[2] == (x[1]+1)%10 && x[3] == (x[2]+1)%10 {
        "Weak"
    } else {
        "Strong"
    };

    println!("{}", ans);
}