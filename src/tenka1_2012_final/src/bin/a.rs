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
        mut n: u64,
    }

    let mut f = vec![0, 1];
    while *f.last().unwrap() <= n {
        let m = f.len();
        let x = f[m-2] + f[m-1];
        f.push(x);
    }

    dbg!("a");

    let mut ans = 0;
    for i in (1..f.len()).rev() {
        while f[i] <= n {
            dbg!(n);
            ans += 1;
            n -= f[i];
        }
    }

    println!("{}", ans);
}