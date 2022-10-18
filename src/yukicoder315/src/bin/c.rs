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
    input!{
        a: usize,
        b: usize,
        c: usize,
        n: usize,
    }

    let m = 51;
    let mut dp = vec![vec![vec![vec![[0.0; 3]; m]; m]; m]; m];

    for i in 1..=n {
        for j in 0..=a {
            for k in 0..=b {
                for l in 0..=c {
                    if j+k+l <= 1 { continue; }
                    let t = ((j+k+l) * (j+k+l-1) / 2) as f64;

                    let p = if j > 0 { (j*(j-1)/2) as f64 / t } else { 0.0 };
                    let q = if k > 0 { (k*(k-1)/2) as f64 / t } else { 0.0 };
                    let r = if l > 0 { (l*(l-1)/2) as f64 / t } else { 0.0 };
                    // eprintln!("{} {} {} {} {} {} {}", i, j, k, l, p, q, r);

                    for h in 0..3 {
                        dp[i][j][k][l][h] += (1.0-p-q-r) * dp[i-1][j][k][l][h];
                    }

                    if j > 0 {
                        dp[i][j][k][l][0] += p * (dp[i-1][j-1][k][l][0] + 1.0);
                        dp[i][j][k][l][1] += p * dp[i-1][j-1][k][l][1];
                        dp[i][j][k][l][2] += p * dp[i-1][j-1][k][l][2];
                    }
                    if k > 0 {
                        dp[i][j][k][l][0] += q * dp[i-1][j][k-1][l][0];
                        dp[i][j][k][l][1] += q * (dp[i-1][j][k-1][l][1] + 1.0);
                        dp[i][j][k][l][2] += q * dp[i-1][j][k-1][l][2];
                    }
                    if l > 0 {
                        dp[i][j][k][l][0] += r * dp[i-1][j][k][l-1][0];
                        dp[i][j][k][l][1] += r * dp[i-1][j][k][l-1][1];
                        dp[i][j][k][l][2] += r * (dp[i-1][j][k][l-1][2] + 1.0);
                    }
                }
            }
        }
    }

    println!("{} {} {}", dp[n][a][b][c][0], dp[n][a][b][c][1], dp[n][a][b][c][2]);
}

pub mod proconio {
    #[macro_export]
    macro_rules! input{
        (sc=$sc:expr,$($r:tt)*)=>{
            input_inner!{$sc,$($r)*}
        };
        ($($r:tt)*)=>{
            let mut sc=proconio::Scanner::new(std::io::stdin().lock());
            input_inner!{sc,$($r)*}
        };
    }

    #[macro_export]
    macro_rules! input_inner{
        ($sc:expr)=>{};
        ($sc:expr,)=>{};
        ($sc:expr,$var:ident:$t:tt$($r:tt)*)=>{
            let $var=read_value!($sc,$t);
            input_inner!{$sc $($r)*}
        };
    }

    #[macro_export]
    macro_rules! read_value{
        ($sc:expr,($($t:tt),*))=>{
            ($(read_value!($sc,$t)),*)
        };
        ($sc:expr,[$t:tt;$len:expr])=>{
            (0..$len).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        };
        ($sc:expr,Chars)=>{read_value!($sc,String).chars().collect::<Vec<char>>()};
        ($sc:expr,Usize1)=>{read_value!($sc,usize)-1};
        ($sc:expr,$t:ty)=>{$sc.next::<$t>()};
    }
    pub struct Scanner {
        s: Box<str>,
        input: std::iter::Peekable<std::str::SplitAsciiWhitespace<'static>>,
    }
    impl Scanner {
        pub fn new<R: std::io::Read>(mut reader: R) -> Self {
            let s = {
                let mut s = String::new();
                reader.read_to_string(&mut s).unwrap();
                s.into_boxed_str()
            };
            let mut sc = Scanner {
                s,
                input: "".split_ascii_whitespace().peekable(),
            };
            use std::mem;
            let s: &'static str = unsafe { mem::transmute(&*sc.s) };
            sc.input = s.split_ascii_whitespace().peekable();
            sc
        }
        #[inline]
        pub fn next<T: std::str::FromStr>(&mut self) -> T
        where
            T::Err: std::fmt::Debug,
        {
            self.input
                .next()
                .unwrap()
                .parse::<T>()
                .expect("Parse error")
        }
    }
}
