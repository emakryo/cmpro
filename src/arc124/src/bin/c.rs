#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn factors(x: usize) -> Vec<usize> {
    let mut fs = vec![];

    for n in 1..x {
        if n * n > x { break; }
        if n * n == x { fs.push(n); }
        else if x % n == 0 {
            fs.push(n);
            fs.push(x/n);
        }
    }

    fs
}

fn gcd(x: usize, y: usize) -> usize {
    if y == 0 { x }
    else { gcd(y, x%y) }
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(usize, usize); n],
    }

    let mut c: Vec<usize> = vec![];

    for &(a, b) in &xs {
        c.extend(factors(a).iter());
        c.extend(factors(b).iter());
    }
    c.sort();
    c.dedup();

    let mut ans = 0;
    for x in c {
        let mut g = vec![];
        let mut ok = true;
        for &(a, b) in &xs {
            let mut h = vec![];
            if a % x == 0 {
                if g.is_empty() {
                    h.push(b);
                } else {
                    for &gi in &g {
                        h.push(gcd(gi, b));
                    }
                }
            }
            if b % x == 0 {
                if g.is_empty() {
                    h.push(a);
                } else {
                    for &gi in &g {
                        h.push(gcd(gi, a));
                    }
                }
            }
            if a % x > 0 && b % x > 0 {
                ok = false;
                break;
            }
            h.sort();
            h.dedup();
            g = h;
        }

        if ok {
            let y = *g.last().unwrap();
            ans = ans.max(x * y / gcd(x, y));
        }
    }

    println!("{}", ans);
}