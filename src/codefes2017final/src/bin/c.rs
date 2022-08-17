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
        d: [usize; n],
    }

    let mut c = vec![0; 13];
    c[0] = 1;
    for di in d {
        c[di] += 1;
    }

    for i in 0..=12 {
        if c[i] >= 3 {
            println!("0");
            return;
        }
    }

    if c[0] >= 2 || c[12] >= 2 {
        println!("0");
        return;
    }

    let mut ans = 1;
    for i in 2..=12 {
        let mut x = c.clone();
        let mut k = 0;
        x[0] -= 1;
        for j in 1..24 {
            if j >= k+i && x[j.min(24-j)] > 0 && j+i <= 24 {
                x[j.min(24-j)] -= 1;
                k = j;
            }
        }
        dbg!(i, &x);

        if *x.iter().max().unwrap() == 0 {
            ans = i;
        }
    }

    println!("{}", ans);
}