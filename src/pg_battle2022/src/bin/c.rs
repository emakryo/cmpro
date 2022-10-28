#![allow(unused_macros, unused_imports)]

use proconio::marker::{Chars, Usize1};
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
        s: Chars,
        t: Chars,
        k: usize,
        ps: [(Usize1, Usize1); k],
    }

    let n_max = 1000000;
    let mut p2 = vec![0; n_max];
    for i in 2..n_max {
        if i%2 == 0 {
            p2[i] = p2[i/2] + 1;
        }
    }
    let mut p2c = vec![0; n_max];
    for i in 1..n_max {
        p2c[i] = p2[i] + p2c[i-1];
    }

    for (x, y) in ps {
        if x == 0 {
            println!("{}", t[y]);
            continue;
        }
        if y == 0 {
            println!("{}", s[x]);
            continue;
        }
        let mut ans = 0;

        for i in 1..=x {
            if s[i] == '1' {
                dbg!(format!("x {} {}C{}={}", i, x-i+y-1, x-i, cm2(x-i+y-1, x-i, &p2c)));
                ans += cm2(x-i+y-1, x-i, &p2c);
            }
        }

        for i in 1..=y {
            if t[i] == '1' {
                dbg!(format!("y {} {}C{}={}", i, x-1+y-i, y-i, cm2(x-1+y-i, y-i, &p2c)));
                ans += cm2(x-1+y-i, y-i, &p2c);
            }
        }

        println!("{}", ans % 2);
    }

}

fn cm2(n: usize, m: usize, p2c: &[usize]) -> usize {
    if p2c[n] == p2c[n-m] + p2c[m] {
        1
    } else {
        0
    }
}
