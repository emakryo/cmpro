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
        s: Chars,
    }

    let mut xs = vec![0];
    for i in 0..n {
        if s[i] == '#' {
            xs.push(0);
        } else {
            *xs.last_mut().unwrap() += 1;
        }
    }

    let x = xs[0];
    let mut y =  xs[xs.len()-1];
    for i in 1..xs.len()-1 {
        if x+y < xs[i] {
            y += xs[i]-x-y;
        }
    }

    println!("{} {}", x, y);
}