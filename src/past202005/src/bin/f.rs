#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;

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
        a: [Chars; n],
    }

    let a = a.into_iter().map(|ai| {
        ai.into_iter().collect::<HashSet<char>>()
    }).collect::<Vec<_>>();

    let mut ans = vec![];
    for i in 0..n/2 {
        let mut ok = false;
        for c in &a[i] {
            if a[n-i-1].contains(c) {
                ans.push(*c);
                ok = true;
                break;
            }
        }
        if !ok {
            println!("-1");
            return;
        }
    }

    let r = ans.iter().rev().cloned().collect::<String>();
    let ans = ans.iter().collect::<String>();
    if n%2 == 1 {
        let c = *a[n/2].iter().next().unwrap();
        println!("{}{}{}", ans, c, r);
    } else {
        println!("{}{}", ans, r);
    }
}