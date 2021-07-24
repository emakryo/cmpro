#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn search(p: i64, k: usize, a: &Vec<Vec<i64>>) -> i64 {
    let (mut lb, mut ub) = (0, 2000000000);

    while ub - lb > 1 {
        let x = (ub + lb) / 2;

        if count(p, x, a) <= k {
            ub = x;
        } else {
            lb = x;
        }
    }

    lb
}

fn count(p: i64, x: i64, a: &Vec<Vec<i64>>) -> usize {
    let n = a.len();
    let mut b = a.clone();
    for i in 0..n {
        for j in 0..n {
            if b[i][j] < 0 {
                b[i][j] = x;
            }
        }
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                b[i][j] = b[i][j].min(b[i][k] + b[k][j]);
            }
        }
    }
    let mut m = 0;
    for i in 0..n {
        for j in i+1..n {
            if b[i][j] <= p {
                m += 1;
            }
        }
    }

    m
}

fn main() {
    proconio::input!{
        n: usize,
        p: i64,
        k: usize,
        a: [[i64; n]; n],
    }

    let mu = count(p, 2000000000, &a);
    let ml = count(p, 0, &a);
 
    if mu == k {
        println!("Infinity");
        return;
    }
    if mu > k {
        println!("0");
        return;
    }

    if ml < k {
        println!("0");
        return;
    }

    let lb = search(p, k, &a);
    let ub = search(p, k-1, &a);
    dbg!(lb, ub);

    println!("{}", ub - lb);
}