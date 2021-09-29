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
        m: usize,
        s: [usize; n],
        t: [usize; m],
    }

    if t.iter().all(|x| *x==s[0]) {
        println!("{}", m);
        return;
    }

    if s.iter().all(|&x| x==s[0]) && !t.iter().all(|&x| x == s[0]) {
        println!("-1");
        return;
    }

    let mut ans = n;
    for i in 0..n {
        if s[i] != s[(i+1)%n] {
            if s[i] == t[0] {
                ans = ans.min(i).min(n-i);
            } else {
                ans = ans.min(i+1).min(n-i-1);
            }
        }
    }
    assert!(ans != n);
    dbg!(ans);

    ans += m;

    for i in 1..m {
        if t[i] != t[i-1] {
            ans += 1;
        }
    }

    println!("{}", ans);
}