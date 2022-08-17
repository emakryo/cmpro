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
        n: i64,
    }

    let mut ans: i64 = 0;

    for a in 1..=n {
        if a * a * a > n {
            break;
        }

        for b in a..=n {
            if a * b * b > n {
                break;
            }

            ans += 0.max(n / a / b - b + 1);
        }
    }

    println!("{}", ans);
}
