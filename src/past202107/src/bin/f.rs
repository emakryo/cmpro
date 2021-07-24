#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(usize, usize, usize); n],
    }

    let mut m = vec![vec![false; 24]; 100001];
    for (d, s, t) in xs {
        for i in s..t {
            if m[d][i] {
                println!("Yes");
                return;
            }
            m[d][i] = true;
        }
    }

    println!("No");
}