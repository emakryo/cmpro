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
        k: usize,
        a: [usize; n],
    }

    let mut ok = 1;
    let mut ng = 1<<62;
    while ng - ok > 1 {
        let x = (ok + ng) / 2;
        let mut t = 0;

        for &ai in &a {
            t += ai.min(x);
        }

        if x <= t / k {
            ok = x;
        } else {
            ng = x;
        }
    }
    println!("{}", ok);
}
