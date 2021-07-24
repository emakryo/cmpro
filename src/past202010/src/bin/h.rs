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
        n: usize,
        m: usize,
        k: usize,
        s: [Bytes; n],
    }

    let mut ans = 1;

    for i in 0..n {
        for j in 0..m {
            for l in 1..(n-i+1).min(m-j+1) {
                let mut cnt = [0; 10];
                for x in i..i+l {
                    for y in j..j+l {
                        let c = s[x][y] - b'0';
                        cnt[c as usize] +=1;
                    }
                }

                let cmax = *cnt.iter().max().unwrap();
                if l * l - cmax <= k {
                    ans = ans.max(l);
                }
            }
        }
    }

    println!("{}", ans);
}