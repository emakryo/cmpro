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
        a: [usize; m],
    }

    let mut x = vec![0; n];

    for ai in a {
        if x[0] < ai {
            x[0] = ai;
            println!("1");
            continue;
        }
        if ai <= x[n-1] {
            println!("-1");
            continue;
        }

        let mut ng = 0;
        let mut ok = n;

        while ok - ng > 1 {
            let m = (ok + ng) / 2;
            if x[m] < ai {
                ok = m;
            } else {
                ng = m;
            }
        }

        println!("{}", ok+1);
        x[ok] = ai;
    }
}