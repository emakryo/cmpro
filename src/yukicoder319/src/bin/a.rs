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
    }

    let mut f = vec![0; 16];
    f[0] = 1;
    for i in 1..16 {
        f[i] = f[i-1] * i;
    }

    println!("{}", f[a|b]);


}
pub mod input {
    use std::{cell::RefCell, io::Read, mem};
    thread_local!(static DONE: RefCell<bool> = RefCell::new(false));

    #[macro_export]
    macro_rules! input{
        (read=$read:expr,$($r:tt)*)=>{
            let mut sc = input::Scanner::new($read);
            input_inner!{sc,$($r)*}
        };
        ($($r:tt)*)=>{
            let mut sc = input::Scanner::default();
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
        ($sc:expr,($($t:tt),*))=>{($(read_value!($sc,$t)),*)};
        ($sc:expr,[$t:tt;$len:expr])=>{
            (0..$len).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        };
        ($sc:expr,[$t:tt])=>{{
            let len = read_value!($sc, usize);
            (0..len).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        }};
        ($sc:expr,Chars)=>{read_value!($sc,String).chars().collect::<Vec<char>>()};
        ($sc:expr,Bytes)=>{read_value!($sc,String).bytes().collect::<Vec<u8>>()};
        ($sc:expr,Usize1)=>{read_value!($sc,usize)-1};
        ($sc:expr,$t:ty)=>{$sc.next::<$t>()};
    }
    pub fn buf_stdin() -> Box<dyn FnMut() -> String> {
        Box::new(|| {
            DONE.with(|f| {
                assert!(!*f.borrow(), "Insufficient input");
                *f.borrow_mut() = true;
            });
            let stdin = std::io::stdin();
            let mut s = String::new();
            stdin.lock().read_to_string(&mut s).unwrap();
            s
        })
    }
    pub fn line_stdin() -> Box<dyn FnMut() -> String> {
        Box::new(|| {
            let stdin = std::io::stdin();
            let mut s = String::new();
            stdin.read_line(&mut s).unwrap();
            s
        })
    }
    pub fn file<P: AsRef<std::path::Path>>(path: P) -> Box<dyn FnMut() -> String> {
        let path = path.as_ref().to_owned();
        Box::new(move || {
            DONE.with(|f| {
                assert!(!*f.borrow(), "Insufficient input");
                *f.borrow_mut() = true;
            });
            std::fs::read_to_string(&path).unwrap()
        })
    }
    pub struct Scanner {
        read_fn: Box<dyn FnMut() -> String>,
        s: Box<str>,
        input: std::str::SplitAsciiWhitespace<'static>,
    }
    impl Default for Scanner {
        fn default() -> Self {
            Self::new(if cfg!(debug_assertions) { line_stdin() } else { buf_stdin() })
        }
    }
    impl Scanner {
        pub fn new(read_fn: Box<dyn FnMut() -> String>) -> Self {
            Self {
                read_fn,
                s: "".into(),
                input: "".split_ascii_whitespace(),
            }
        }
        pub fn next<T: std::str::FromStr>(&mut self) -> T
        where
            T::Err: std::fmt::Debug,
        {
            if let Some(v) = self.input.next() {
                v.parse::<T>().expect("Parse error")
            } else {
                self.s = (&mut self.read_fn)().into_boxed_str();
                let s: &'static str = unsafe { mem::transmute(&*self.s) };
                self.input = s.split_ascii_whitespace();
                self.next()
            }
        }
    }
}