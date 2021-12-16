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
        k: usize,
        a: Bytes,
        b: Bytes,
    }

    let mut x = 0;
    for ai in a {
        x *= k;
        x += (ai-b'0') as usize;
    }

    let mut y = 0;
    for bi in b {
        y *= k;
        y += (bi-b'0') as usize;
    }

    println!("{}", x*y);
}