#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;

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

fn rec(k: usize, xs: &[&[char]]) -> Option<usize> {
    if k == 0 {
        let n = xs[0].len();
        if n == 0 {
            return Some(0);
        }
        if n == 1 {
            return None;
        }
        let mut r = 0;

        let mut cnt = vec![HashMap::new(); n];
        for i in 0..n {
            for j in 0..xs.len() {
                let c = if j%2 == 0 {
                    xs[j][i]
                } else {
                    xs[j][n-i-1]
                };
                *cnt[i].entry(c).or_insert(0) += 1;
            }
        }

        let mut ok = false;
        let mut cand = vec![xs.len()];
        for i in 0..n/2 {
            let mut a = cnt[i].iter().map(|(&x, &y)| (y, x)).collect::<Vec<_>>();
            a.sort(); a.reverse();

            let mut b = cnt[n-i-1].iter().map(|(&x, &y)| (y, x)).collect::<Vec<_>>();
            b.sort(); b.reverse();

            if a[0].1 != b[0].1 {
                ok = true;
            }
            r += 2*xs.len() - a[0].0 - b[0].0;
            if a.len() > 1 {
                cand.push(a[0].0-a[1].0);
            }
            if b.len() > 1 {
                cand.push(b[0].0-b[1].0);
            }
        }

        if n%2 > 0 {
            r += xs.len() - cnt[n/2].values().max().unwrap();
        }

        if !ok {
            cand.sort();
            r += cand[0];
        }

        Some(r)
    } else {
        let mut ys = vec![];
        let mut cnt = HashMap::new();
        let n = xs[0].len();
        if n == 0 {
            return None;
        }
        for x in xs {
            if n % 2 > 0 {
                *cnt.entry(x[n/2]).or_insert(0) += 1;
                ys.push(&x[..n/2]);
                ys.push(&x[n/2+1..]);
            } else {
                ys.push(&x[..n/2]);
                ys.push(&x[n/2..]);
            }
        }
        let m = if n % 2 > 0 {
            cnt.values().sum::<usize>() - cnt.values().max().unwrap()
        } else {
            0
        };
        rec(k-1, &ys).map(|x| x + m)
    }
}

fn main() {
    proconio::input!{
        k: usize,
        s: Chars,
    }

    if let Some(a) = rec(k, &[&s[..]]) {
        println!("{}", a);
    } else {
        println!("impossible");
    }
}