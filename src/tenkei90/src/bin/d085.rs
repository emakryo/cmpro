#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        k: usize,
    }
    if k==1 {
        println!("{}", 1);
        return;
    }

    let mut ans = 0usize;
    for i in 1..k {
        if i*i > k { break }
        if k % i > 0 { continue }
        let n = k / i;
        for j in i..n {
            if n / j < j { break }
            if n % j > 0 { continue }
            dbg!(i, j);
            ans += 1;
        }

    }

    println!("{}", ans);
}