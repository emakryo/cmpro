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
    ans += count(g.0 - s.0, g.1 - s.1, w, h, t, &sqs);
    ans += count(g.0 - s.0, 2 * h - g.1 - s.1, w, h, t, &sqs);
    ans += count(2 * w - g.0 - s.0, g.1 - s.1, w, h, t, &sqs);
    ans += count(2 * w - g.0 - s.0, 2 * h - g.1 - s.1, w, h, t, &sqs);

    println!("{}", ans);
}


fn count(a: i64, b: i64, w: i64, h: i64, t: i64, sqs: &BTreeMap<i64, i64>) -> i32 {
    let mut ret = 0;

    for x in -t..=t {
        let m2 = t * t - (2 * w * x - a).pow(2);
        if let Some(&m) = sqs.get(&m2) {
            if (m - b).abs() % (2 * h) == 0 {
                ret += 1;
            }

            if m > 0 && (-m - b).abs() % (2 * h) == 0 {
                ret += 1;
            }
        }
    }

    ret
}