#![allow(unused_macros, unused_imports)]

use std::collections::{HashMap, HashSet};

use proconio::marker::Chars;
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn gcd(x: i64, y: i64) -> i64 {
    if y == 0 { x }
    else { gcd(y, x%y) }
}

fn main() {
    proconio::input!{
        s: Chars,
        k: i64,
    }

    let mut xs = vec![];
    let mut p = (0, 0);
    xs.push(p);
    for c in s {
        match c {
            'L' => p.0 -= 1,
            'R' => p.0 += 1,
            'U' => p.1 -= 1,
            'D' => p.1 += 1,
            _ => (),
        }
        xs.push(p);
    }

    if p.0 < 0 {
        xs.iter_mut().for_each(|x| {
            x.0 = -x.0;
        });
        p.0 = -p.0;
    }
    if p.1 < 0 {
        xs.iter_mut().for_each(|x| {
            x.1 = -x.1;
        });
        p.1 = -p.1;
    }

    if p.0 == 0 {
        xs.iter_mut().for_each(|x| {
            *x = (x.1, x.0);
        });
        p = (p.1, p.0);
    }

    xs.sort();
    xs.dedup();

    if p == (0, 0) {
        println!("{}", xs.len());
        return;
    }

    dbg!(p);
    assert!(p.0 > 0 && p.1 >= 0);


    let g = if p.1 > 0 {
        gcd(p.0, p.1)
    } else {
        p.0
    };

    p.0 /= g;
    p.1 /= g;

    let mut i2p = HashMap::<_, (i64, i64)>::new();
    let mut i2k = HashMap::<_, Vec<i64>>::new();

    for x in &xs {
        let b = (p.0*x.1-p.1*x.0, p.0);
        let b = if b.0 == 0 {
            (0, 1)
        } else {
            let g = gcd(b.0.abs(), b.1);
            (b.0 / g, b.1 / g)
        };

        if let Some(&q) = i2p.get(&b) {
            let k = (x.0-q.0) / p.0;
            i2k.get_mut(&b).unwrap().push(k);
        } else {
            i2p.insert(b, *x);
            i2k.insert(b, vec![0]);
        }
    }
    dbg!(&i2k);

    let mut ans = 0;

    for (_, ks) in i2k.iter_mut() {
        let k_min = *ks.iter().min().unwrap();
        ks.iter_mut().for_each(|k| {
            *k = *k - k_min;
        });

        let mut tss = HashMap::new();
        for k in ks {
            tss.entry(*k%g).or_insert(vec![]).push(*k/g);
        }

        for (_, ts) in &mut tss {
            ts.sort();
            let mut last = -1i64;
            let mut a = 0;
            dbg!(&ts);
            for t in ts {
                let t = *t;
                if last < t {
                    a += k;
                } else {
                    a += t + k - last;
                }
                last = k + t;
            }
            dbg!(a);
            ans += a;
        }
    }

    println!("{}", ans);
}