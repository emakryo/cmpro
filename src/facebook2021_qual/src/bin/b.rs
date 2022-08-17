#![allow(unused_macros, unused_imports)]

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

fn main() {
    proconio::input!{
        t: usize
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        c: [Chars; n],
    }

    let mut ans = vec![];
    for i in 0..n {
        let mut e = 0;
        let mut ok = true;
        for j in 0..n {
            if c[i][j] == '.' {
                e += 1;
            } else if c[i][j] == 'O' {
                ok = false;
            }
        }

        if ok && e > 0{
            ans.push(e);
        }

        let mut e = 0;
        let mut ok = true;
        for j in 0..n {
            if c[j][i] == '.' {
                e += 1;
            } else if c[j][i] == 'O' {
                ok = false;
            }
        }

        if ok && e > 0{
            ans.push(e);
        }
    }

    if ans.is_empty() {
        println!("Impossible");
    } else {
        ans.sort();
        let x = ans[0];
        if x > 1 {
            println!("{} {}", x, ans.iter().filter(|&&a| a==x).count());
        } else {
            let mut k = 0;
            for i in 0..n {
                for j in 0..n {
                    if c[i][j] != '.' { continue }
                    let p = c[i].iter().filter(|&&x| x=='X').count();
                    let q = c.iter().map(|x| x[j]).filter(|&x| x=='X').count();
                    if p == n-1 || q == n-1 {
                        k += 1;
                    }
                }
            }

            println!("{} {}", x, k);
        }
    }
}