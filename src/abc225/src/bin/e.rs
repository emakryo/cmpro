#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
struct Rat(i64, i64);

impl From<(i64, i64)> for Rat {
    fn from(x: (i64, i64)) -> Self {
        fn gcd(a: i64, b: i64) -> i64 {
            if b == 0 {
                a
            } else {
                gcd(b, a % b)
            }
        }

        if x == (0, 0) {
            Rat(0, 0)
        } else if x.0 == 0 {
            Rat(0, x.1 / x.1.abs())
        } else if x.1 == 0 {
            Rat(x.0 / x.0.abs(), 0)
        } else {
            let g = gcd(x.0.abs(), x.1.abs());
            Rat(x.0 / g, x.1 / g)
        }
    }
}

impl PartialOrd for Rat {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some((self.1 * other.0).cmp(&(other.1 * self.0)))
    }
}

impl Ord for Rat {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.partial_cmp(other).unwrap()
    }
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(i64, i64); n],
    }

    let ac = solve_ac(xs.clone());
    let wa = solve_wa(xs.clone());
    if ac != wa {
        dbg!(ac, wa, xs);
    }
}

fn solve_ac(xs: Vec<(i64, i64)>) -> u64 {
    let mut xs = xs
        .into_iter()
        .map(|x| (Rat::from((x.0-1, x.1)), Rat::from((x.0, x.1-1))))
        .collect::<Vec<_>>();
    
    xs.sort();

    let mut ans = 1;
    let mut last = xs[0].0;
    for (a, b) in xs {
        if last <= b {
            last = a;
            ans += 1;
        }
    }

    ans
}

fn solve_wa(mut xs: Vec<(i64, i64)>) -> u64 {
    xs.sort_by_key(|&x| Rat::from((x.0-1, x.1)));

    let mut dp = BTreeMap::<Rat, u64>::new();

    for x in xs {
        dbg!(x);
        let y = Rat::from((x.0, x.1-1));
        // この方針だとy以下の全てのmaxを取らないといけない（最後だけじゃだめ）頭がついてない
        let k = *dp.range(..=y).rev().next().map(|e| e.1).unwrap_or(&0);
        let d = dp.entry(Rat::from((x.0-1, x.1))).or_default();
        *d = (k+1).max(*d);
    }
    dbg!(&dp);

    *dp.values().max().unwrap()
}