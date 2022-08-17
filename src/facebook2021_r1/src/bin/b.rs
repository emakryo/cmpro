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
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        m: usize,
        a: usize,
        b: usize,
    }

    if a.min(b) < n+m-1 {
        println!("Impossible");
        return;
    }

    let a = a - (n-2) - (m-2);
    let b = b - (n-2) - (m-2);

    let s = (((a + b) as f64 * 2.0 / 3.0).floor() as usize).max(b+1).max(a+1);
    let x = s - b;
    let y = s - a;
    let zw  = a + b - s;
    let w = x.min(zw-1);
    let z = zw - w;
    
    let mut ans = vec![vec![1000; m]; n];
    for i in 1..m-1 {
        ans[0][i] = 1;
    }
    for i in 1..n-1 {
        ans[i][0] = 1;
    }

    if m < n {
        for i in 1..m-1 {
            ans[n-1][i] = 1;
        }
        ans[0][0] = w;
        ans[0][m-1] = y;
        ans[n-1][0] = z;
        ans[n-1][m-1] = x;
    } else {
        for i in 1..n-1 {
            ans[i][m-1] = 1;
        }
        ans[0][0] = w;
        ans[0][m-1] = z;
        ans[n-1][0] = y;
        ans[n-1][m-1] = x;
    }


    println!("Possible");
    for i in 0..n {
        println!("{}", ans[i].iter().map(ToString::to_string).collect::<Vec<_>>().join(" "));
    }
}