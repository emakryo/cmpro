#![allow(unused_macros, unused_imports)]

use std::iter::repeat;

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
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input!{
        r: usize,
        c: usize,
        s: [Chars; r],
    }

    if r == 1 || c == 1 {
        if s.iter().any(|l| l.iter().any(|x| *x == '^')) {
            println!("Impossible");
        } else {
            println!("Possible");
            for l in s {
                println!("{}", l.into_iter().collect::<String>());
            }
        }
        return
    }


    println!("Possible");
    for _ in 0..r {
        println!("{}", repeat('^').take(c).collect::<String>());
    }

}
