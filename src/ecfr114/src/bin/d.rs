#![allow(unused_macros, unused_imports)]

use std::collections::{BinaryHeap, HashSet};
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
    let mut sc=proconio::Scanner::new(std::io::stdin().lock());
    input! {
        sc=sc,
        n: usize,
        a: [[i64]; n],
        m: usize,
        b: [[usize; n]; m],
    }

    let mut s = HashSet::new();
    // dbg!(&b);
    for bi in b {
        s.insert(bi.into_iter().map(|x| x-1).collect::<Vec<_>>());
    }
    dbg!(&s);


    let mut heap = BinaryHeap::new();
    let x: i64 = a.iter().map(|ai| ai.last().unwrap()).sum();
    let p = a.iter().map(|ai| ai.len()-1).collect::<Vec<usize>>();
    let mut done = HashSet::new();

    heap.push((x, p));
    
    loop {
        let (_, mut p) = heap.pop().unwrap();
        if !s.contains(&p) {
            println!("{}", p.iter().map(|x| (x+1).to_string()).collect::<Vec<String>>().join(" "));
            return;
        }

        for i in 0..n {
            if p[i] == 0 { continue; }

            p[i] -= 1;
            let x: i64 = a.iter().zip(p.iter()).map(|(ai, &j)| ai[j]).sum();

            if !done.contains(&p) {
                heap.push((x, p.clone()));
                done.insert(p.clone());
            }
            p[i] += 1;
        }

    }
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
        ($sc:expr,[$t:tt])=>{{
            let n = read_value!($sc, usize);
            (0..n).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        }};
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
