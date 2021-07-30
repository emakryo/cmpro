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

#[proconio::fastout]
fn main() {
    proconio::input!{
        n: usize,
        a: [usize; n],
        b: [usize; n],
    }

    let mut ans = 0;
    let mut a_max = 0;
    for i in 0..n {
        a_max = a_max.max(a[i]);
        ans = ans.max(a_max * b[i]);
        println!("{}", ans);
    }
}