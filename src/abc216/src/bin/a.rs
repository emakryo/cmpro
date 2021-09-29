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
        s: Bytes,
    }

    let mut x = vec![];
    let mut y = 0;
    let mut f = false;
    for c in s {
        if c == b'.' {
            f = true;
        } else if f {
            y = c;
        } else {
            x.push(c);
        }
    }

    let x = x.iter().map(|&x| x as char).collect::<String>();
    if (b'0'..=b'2').contains(&y) {
        println!("{}-", x);
    } else if (b'3'..=b'6').contains(&y) {
        println!("{}", x);
    } else {
        println!("{}+", x);
    }
}