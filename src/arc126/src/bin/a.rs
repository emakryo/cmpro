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
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: [usize; 3],
    }

    let n2 = n[0];
    let n4 = n[2];
    let n6 = n[1]/2;

    let x46 = n6.min(n4);
    let n4 = n4-x46;
    let n6 = n6-x46;

    let x226 = n6.min(n2/2);
    let n6 = n6 - x226;
    let n2 = n2 - x226*2;

    let x244 = (n4/2).min(n2);
    let n4 = n4 - 2 * x244;
    let n2 = n2 - x244;

    let x2224 = n4.min(n2/3);
    let n4 = n4 - x2224;
    let n2 = n2 - 3 * x2224;

    let x22222 = n2/5;

    println!("{}", x46+x226+x244+x2224+x22222);
}