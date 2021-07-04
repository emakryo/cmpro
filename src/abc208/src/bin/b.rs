#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        mut p: usize,
    }

    let mut d = vec![1];
    for i in 2..=10 {
        let x = *d.last().unwrap() * i;
        d.push(x);
    }

    d.reverse();
    let mut ans = 0;
    for x in d {
        ans += p / x;
        p = p % x;
    }

    println!("{}", ans);

}