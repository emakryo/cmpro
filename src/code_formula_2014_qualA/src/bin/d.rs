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
        s: String,
        k: String,
    }
    let s = s.chars().collect::<Vec<_>>();
    let mut k = k.chars().collect::<Vec<_>>();

    let n = 36 - k.len();
    let mut m = 0;
    for &c in &s {
        if !k.contains(&c) {
            m += 1;
            k.push(c);
        }
    }

    let mut memo = vec![vec![vec![None; 55]; 55]; 55];
    dbg!(n, m);

    println!("{}", f(m, n, 0, &mut memo) + (s.len() - m) as f64);
}

fn f(i: usize, k: usize, n: usize, memo: &mut Vec<Vec<Vec<Option<f64>>>>) -> f64 {
    if let Some(x) = memo[i][k][n] {
        return x;
    }

    let mut x = 0.0;
    if i == 0 {
        x = 0.0;
    } else if k <= 1 {
        x = f(i-1, 0, 0, memo) + 1.0;
    } else {
        let kf = k as f64;
        let nf = n as f64;
        if nf > 0.0 {
            x += nf / (kf+nf) * (1.0 + f(i-1, k, n-1, memo));
        }
        
        for j in 1..=k {
            x += (2.0 * j as f64 - 1.0 + f(i-1, k-j, n+j-1, memo)) / (kf+nf);
        }
    }
    
    memo[i][k][n] = Some(x);
    x
}