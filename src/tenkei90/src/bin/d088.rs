#![allow(unused_macros, unused_imports)]

use proconio::marker::Usize1;
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        q: usize,
        a: [usize; n],
        es: [(usize, usize); q]
    }

    let mut adj = vec![vec![0u32; n+1]; n+1];
    for (x, y) in es {
        adj[x][y] = 1;
        adj[y][x] = 1;
    }

    let m = 9000;
    let mut dp: Vec<Vec<usize>> = vec![vec![]; m];

    for i in 0..n {
        let mut next = dp.clone();

        for j in 0..=m {
            if j+a[i] >= m {
                continue;
            }
            if j > 0 && dp[j].len() == 0 {
                continue;
            }

            let mut x = dp[j].clone();
            let mut ok = true;
            for &xi in &x {
                if adj[xi][i+1] > 0 {
                    ok = false;
                }
            }
            if !ok { continue }
            x.push(i+1);

            if dp[j+a[i]].len() > 0 {
                let s = dp[j+a[i]].iter().map(|x| x.to_string()).collect::<Vec<_>>();
                println!("{}", s.len());
                println!("{}", s.join(" "));
                let t = x.iter().map(|x| x.to_string()).collect::<Vec<_>>();
                println!("{}", t.len());
                println!("{}", t.join(" "));
                return;
            } else {
                next[j+a[i]] = x;
            }
        }

        dp = next;
    }

}