#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeSet, BTreeMap};
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
        w: i64,
        h: i64,
        t: i64,
        s: (i64, i64),
        g: (i64, i64),
    }

    let sqs: BTreeMap<i64, i64> = (0..1000000).map(|i| (i*i, i)).collect();

    let mut ans = 0;
    for p in -t..=t {
        let m2 = t * t - (w * p + g.0 - s.0).pow(2);
        if let Some(&m) = sqs.get(&m2) {
            if (m - (g.1 - s.1)).abs() % h == 0 {
                ans += 1;
            }

            if m > 0 && (- m - (g.1 - s.1)).abs() % h == 0 {
                ans += 1;
            }
        }
    }

    println!("{}", ans);
}
