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
        n: usize,
        m: usize,
        q: usize,
    }

    let mut n_solved = vec![0; m];
    let mut solved = vec![0u64; n];

    for _ in 0..q {
        proconio::input! { t: usize }
        if t == 1 {
            proconio::input! { a: usize }
            let mut ans = 0;
            for i in 0..m {
                if solved[a-1]>>i&1 == 1 {
                    ans += n - n_solved[i];
                }
            }
            println!("{}", ans);
        } else {
            proconio::input! { a: usize, b: usize }
            n_solved[b-1] += 1;
            solved[a-1] += 1 << (b-1);
        }
    }
}