#![allow(unused_macros, unused_imports)]
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
        mut a: [i64; n],
        mut b: [i64; m],
    }

    a.sort();
    b.sort();

    let mut ans = i64::max_value();
    for ai in a {
        let r = b.binary_search(&ai);
        if r.is_ok() {
            ans = 0;
        } else {
            let k = r.unwrap_err();
            if k < m {
                ans = ans.min((ai-b[k]).abs());
            }
            if k > 0 {
                ans = ans.min((ai-b[k-1]).abs());
            }
        }
    }

    println!("{}", ans);
}