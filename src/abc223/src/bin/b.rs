#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;

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
        s: Chars,
    }

    let mut amin = s.clone();
    let mut amax = s.clone();

    let mut s = VecDeque::from(s);

    for _ in 1..s.len() {
        let c = s.pop_front().unwrap();
        s.push_back(c);

        amin = amin.min(s.iter().cloned().collect());
        amax = amax.max(s.iter().cloned().collect());
    }

    println!("{}", amin.iter().collect::<String>());
    println!("{}", amax.iter().collect::<String>());
}