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
        s: [String; 3],
        t: Bytes,
    }

    let mut ans = String::new();

    for c in t {
        let c = (c - b'1') as usize;
        ans.extend(s[c].chars());
    }

    println!("{}", ans);
}