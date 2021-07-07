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
        s: proconio::marker::Bytes,
    }

    let mut last = (n, n);
    let mut nearest = vec![n; n];
    for i in (0..n).rev() {
        if s[i] == b'o' {
            nearest[i] = last.1;
            last.0 = i;
        } else {
            nearest[i] = last.0;
            last.1 = i;
        }
    }

    let mut ans = 0;
    for i in 0..n {
        ans += n - nearest[i];
    }

    println!("{}", ans);
}