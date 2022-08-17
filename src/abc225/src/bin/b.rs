#![allow(unused_macros, unused_imports)]

use proconio::marker::Usize1;
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
        es: [(Usize1, Usize1); n-1],
    }

    let mut deg = vec![0; n];
    for (a, b) in es {
        deg[a] += 1;
        deg[b] += 1;
    }

    if *deg.iter().max().unwrap() == n-1 {
        println!("Yes");
    } else {
        println!("No");
    }
}