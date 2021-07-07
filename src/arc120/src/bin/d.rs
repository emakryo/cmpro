#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        a: [usize; 2*n],
    }

    let mut ai: Vec<_> = a.iter().enumerate().map(|(x, &y)| (y, x)).collect();
    ai.sort();

    let mut b = vec![false; 2*n];
    for i in 0..n {
        b[ai[i].1] = true;
    }

    let mut ans = String::new();
    let mut st = 0;
    let mut sf = 0;
    for i in 0..2*n {
        if b[i] {
            if sf == 0 {
                ans += "(";
                st += 1;
            } else {
                ans += ")";
                sf -= 1;
            }
        } else {
            if st == 0 {
                ans += "(";
                sf += 1;
            } else {
                ans += ")";
                st -= 1;
            }
        }
    }

    println!("{}", ans);
}