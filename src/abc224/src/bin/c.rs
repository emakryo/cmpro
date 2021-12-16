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
        xs: [(i64, i64); n],
    }

    let mut ans = 0;
    for i in 0..n {
        for j in i+1..n {
            for k in j+1..n {
                if ccw(xs[i], xs[j], xs[k]).abs() == 1 {
                    ans += 1;
                }
            }
        }
    }
    println!("{}", ans);
}

// Point
pub type P = (i64, i64);

pub fn cross(a: P, b: P) -> i64 {
    a.0 * b.1 - a.1 * b.0
}
pub fn dot(a: P, b: P) -> i64 {
    a.0 * b.0 + a.1 * b.1
}

pub fn ccw(a: P, b: P, c:P) -> i32 {
    let b = (b.0-a.0, b.1-a.1);
    let c = (c.0-a.0, c.1-a.1);
    if cross(b, c) > 0.into() { 1 } // counter clockwise
    else if cross(b, c) < 0.into() { -1 } // clockwise
    else if dot(b, c) < 0.into() { 2 } // c -- a -- b on line
    else if dot(b, b) < dot(c, c) { -2 } // a -- b -- c on line (including a == b)
    else { 0 } // a -- c -- b on line (including b == c and a == c)
}
