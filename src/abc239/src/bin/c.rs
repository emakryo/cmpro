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
        x1: i64,
        y1: i64,
        x2: i64,
        y2: i64,
    }

    let n = 8;
    let dx = [-2, -2, -1, -1, 1, 1, 2, 2];
    let dy = [-1, 1, -2, 2, -2, 2, -1, 1];

    let mut ans = false;
    for i in 0..n {
        for j in 0..n {
            if x1 + dx[i] == x2 + dx[j] && y1 + dy[i] == y2 + dy[j] {
                ans = true;
            }
        }
    }

    println!("{}", if ans { "Yes" } else { "No" });
}
