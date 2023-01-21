#![allow(unused_macros, unused_imports)]

use proconio::marker::{Usize1, Chars, Bytes};
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

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        s: Bytes,
        q: usize,
        rs: [(Usize1, Usize1); q]
    }

    let n = s.len();
    let mut c = vec![vec![0i32; 26]; n+1];

    for i in 0..n {
        for j in 0..26 {
            c[i+1][j] = c[i][j];
            if s[i] - b'a' == j as u8 {
                c[i+1][j] += 1;
            }
        }
    }

    let mut ans = 0;
    for (l, r) in rs {
        let r = r + 1;
        if (r - l) % 2 == 0 {
            continue;
        }

        let mut lc1 = vec![0; 26];
        let mut rc1 = vec![0; 26];

        let mut lc2 = vec![0; 26];
        let mut rc2 = vec![0; 26];
        for i in 0..26 {
            lc1[i] = c[(r+l)/2][i] - c[l][i];
            rc1[i] = c[r][i] - c[(r+l)/2][i];

            lc2[i] = c[(r+l+1)/2][i] - c[l][i];
            rc2[i] = c[r][i] - c[(r+l+1)/2][i];
        }
        // dbg!(r, l, (r+l)/2, (r+l+1)/2);

        // dbg!(&lc1, &rc1, &lc2, &rc2);

        let mut d1 = false;
        let mut d2 = false;
        let mut ok1 = true;
        let mut ok2 = true;

        for i in 0..26 {
            if lc1[i] != rc1[i] {
                if lc1[i].abs_diff(rc1[i]) == 1 {
                    if d1 {
                        ok1 = false;
                    }
                    d1 = true;
                } else {
                    ok1 = false;
                }
            }

            if lc2[i] != rc2[i] {
                if lc2[i].abs_diff(rc2[i]) == 1 {
                    if d2 {
                        ok2 = false;
                    }
                    d2 = true;
                } else {
                    ok2 = false;
                }
            }
        }
        if ok1 && d1 || ok2 && d2 {
            ans += 1;
        }
    }

    println!("{}", ans);
}
