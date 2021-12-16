#![allow(unused_macros, unused_imports)]

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
        mut s: Chars,
        t: Chars,
    }

    if s == t {
        println!("Yes");
        return;
    }

    let n = s.len();

    for i in 0..n-1 {
        s.swap(i, i+1);
        if s == t {
            println!("Yes");
            return;
        }
        s.swap(i, i+1);
    }

    println!("No");
}