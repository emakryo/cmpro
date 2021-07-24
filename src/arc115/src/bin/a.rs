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
        m: usize,
        s: [Chars; n],
    }

    let mut ans = 0u64;
    let mut cnt = [0, 0];
    for i in 0..n {
        let k = s[i].iter().filter(|&&c| c == '1').count();
        ans += cnt[1-k%2];
        cnt[k%2] += 1;
    }

    println!("{}", ans);
}