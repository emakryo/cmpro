#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        k: usize,
        a: [usize; n],
    }

    let mut ans = vec![k / n; n];
    let k = k % n;
    let mut ai: Vec<_> = a.into_iter().enumerate().map(|(a, b)| (b, a)).collect();
    ai.sort();

    for i in 0..k {
        ans[ai[i].1] += 1;
    }

    for i in 0..n {
        println!("{}", ans[i]);
    }

}