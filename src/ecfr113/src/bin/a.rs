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
    let mut sc = proconio::Scanner::new(std::io::stdin().lock());
    input!{
        sc = sc,
        t: usize
    };

    for _ in 0..t {
        input!{
            sc = sc,
            n: usize,
            s: String,
        }
        solve(n, s);
    }

}

fn solve(n: usize, s: String) {
    let s = s.chars().collect::<Vec<char>>();

    for i in 0..n-1 {
        if s[i] == 'a' && s[i+1] == 'b' || s[i] == 'b' && s[i+1] == 'a' {
            println!("{} {}", i+1, i+2);
            return;
        }
    }
    println!("-1 -1");
}

pub mod proconio {
    #[macro_export]
    macro_rules! input{
        {sc=$sc:expr,$($r:tt)*}=>{
            input_inner!{$sc,$($r)*}
        };
        {$($r:tt)*}=>{
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
