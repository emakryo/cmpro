#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        s: proconio::marker::Bytes,
        l: usize,
        r: usize,
    }

    let ans;
    if s.len() > 1 && s[0] == b'0' {
        ans = false;
    } else if s.len() > 10 {
        ans = false;
    } else {
        let mut x = 0;
        for c in s {
            x = 10*x + (c - b'0') as usize;
        }
        ans = (l..r+1).contains(&x);
    }

    println!("{}", if ans { "Yes" } else { "No" });
}