#![allow(unused_macros, unused_imports)]
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
        h: usize,
        w: usize,
        n: usize,
        xs: [(usize, usize); n],
    }

    let mut a: Vec<_> = xs.iter().map(|x| x.0).collect();
    a.sort();
    a.dedup();
    let mut b: Vec<_> = xs.iter().map(|x| x.1).collect();
    b.sort();
    b.dedup();

    for (ai, bi) in &xs {
        println!("{} {}", a.binary_search(ai).unwrap()+1, b.binary_search(bi).unwrap()+1);
    }
}