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
        mut n: usize,
    }

    let mut ans = vec![];
    while n > 0 {
        if n & 1 == 1 {
            ans.push('A');
        }
        n = n >> 1;
        if n > 0 {
            ans.push('B');

        }
    }

    let ans = ans.into_iter().rev().collect::<String>();
    println!("{}", ans);
}