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
        a: [i64; n],
    }

    let (mut lb, mut ub) = (0, 1i64<<32);
    let m = (n * (n + 1) / 2 + 1) / 2;

    while ub - lb > 1 {
        let x = (ub + lb) / 2;
        if m <= count(x, &a) {
            lb = x;
        } else {
            ub = x;
        }
    }

    println!("{}", lb);
}

fn count(x: i64, a: &[i64]) -> usize {
    let mut cum = 0;
    let mut ret = 0;
    let mut up = 0;
    let os = 100005;
    let mut d = vec![0; 2*os as usize];
    for &ai in a {
        if x <= ai {
            cum -= 1;
            d[(cum+os+1) as usize] += 1;
            up += d[(cum+os) as usize] + 1;
            ret += up;
        } else {
            cum += 1;
            up -= d[(cum+os-1) as usize];
            d[(cum+os-1) as usize] += 1;
            ret += up;
        }
    }
    ret
}