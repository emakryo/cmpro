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
        mut a: [i64; n],
    }

    let mut aa = a.clone();
    aa.extend(a.iter());

    let total: i64 = a.iter().sum();
    let mut ans = total;
    let mut sum = 0;
    let mut j = 0;
    for i in 0..2*n {
        while j < 2*n && sum <= total / 2 {
            sum += aa[j];
            j += 1;
            ans = ans.min((total-2*sum).abs());
        }
        sum -= aa[i];
        ans = ans.min((total-2*sum).abs());
    }

    println!("{}", ans);
}