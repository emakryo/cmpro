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
        n: usize,
        m: usize,
        k: u32,
        a: [u64; n],
        es: [(Usize1, Usize1, u64); m],
    }

    let inf = 1u64 << 60;
    let mut dist = vec![vec![inf; n]; n];
    for (x, y, z) in es {
        dist[x][y] = z;
        dist[y][x] = z;
    }
    for i in 0..n {
        dist[i][i] = 0;
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                dist[i][j] = dist[i][j].min(dist[i][k] + dist[k][j]);
            }
        }
    }

    let mut dp = vec![inf; 1<<n];

    for i in 0..n {
        dp[1<<i] = a[i];
    }

    for s in 1..1<<n {
        for i in 0..n {
            if s>>i&1 == 1 {
                continue;
            }

            let mut k = None;

            for j in 0..n {
                if s>>j&1 == 0 {
                    continue;
                }

                if let Some(kk) = k {
                    if dist[i][j] < dist[i][kk] {
                        k = Some(j);
                    }
                } else {
                    k = Some(j);
                }
            }

            if let Some(k) = k {
                dp[s|1<<i] = dp[s|1<<i].min(dp[s] + a[i] + dist[i][k]);
            }
        }
    }

    let mut ans = inf;    
    for s in 0usize..1<<n {
        if s.count_ones() == k {
            ans = ans.min(dp[s]);
        }
    }

    println!("{}", ans);
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
