#![allow(unused_macros, unused_imports)]

use std::vec;
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn gcd(x: i64, y: i64) -> i64 {
    if y == 0 { x }
    else { gcd(y, x % y) }
}

fn main() {
    proconio::input!{
        s: String,
    }

    let k = s.char_indices().find(|(_, c)| *c == '/').unwrap().0;
    let x = s[..k].parse::<i64>().unwrap();
    let y = s[k+1..].parse::<i64>().unwrap();
    let g= gcd(x, y);
    let x = x / g;
    let y = y / g;

    dbg!(x, y);

    let mut ans = vec![];
    let l = (2*x-y)/(y*y);

    for i in 0..5 {
        let k = l + i;
        let n = k * y;
        let m = n * (n + 1) / 2 - k * x;
        if (1..=n).contains(&m) {
            ans.push((n, m));
        }
    }

    if ans.len() == 0 {
        println!("Impossible");
    } else {
        for (n, m) in ans {
            println!("{} {}", n, m);
        }
    }
}