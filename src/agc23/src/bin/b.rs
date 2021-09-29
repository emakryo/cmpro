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
        n: usize,
        s: [Chars; n],
    }

    let mut ans = 0;
    for i in 0..n {
        let mut ok = true;
        for x in 0..n {
            for y in 0..n {
                if s[(x+i)%n][y] != s[(y+i)%n][x] {
                    ok = false;
                }
            }
        }
        if ok {
            ans += n;
        }
    }

    println!("{}", ans);
}