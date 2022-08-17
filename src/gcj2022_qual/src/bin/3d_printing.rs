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

pub mod input {
    use std::{cell::RefCell, io::Read};

    #[macro_export]
    macro_rules! input{
        (scan=$scan:expr,$($r:tt)*)=>{
            input_inner!{$scan,$($r)*}
        };
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
    pub fn stdin(buffered: bool) -> Box<dyn FnMut() -> String> {
        Box::new(move || {
            let stdin = std::io::stdin();
            let mut s = String::new();
            if buffered {
                stdin.lock().read_to_string(&mut s).unwrap();
            } else {
                stdin.read_line(&mut s).unwrap();
            }
            s
        })
    }
    pub fn file<P: AsRef<std::path::Path>>(path: P) -> Box<dyn FnMut() -> String> {
        thread_local!(static DONE: RefCell<bool> = RefCell::new(false));
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
            Self::new(stdin(!cfg!(debug_assertions)))
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
                let s: &'static str = unsafe { std::mem::transmute(&*self.s) };
                self.input = s.split_ascii_whitespace();
                self.next()
            }
        }
    }
}
fn main() {
    let mut scan = input::Scanner::default();
    input!{
        scan=&mut scan,
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve(&mut scan);
    }
}

fn solve(scan: &mut input::Scanner) {
    input! {
        scan=scan,
        x: [[i64; 4]; 3],
    }

    let x = (0..4).map(|i| x[0][i].min(x[1][i]).min(x[2][i])).collect::<Vec<_>>();
    if x.iter().sum::<i64>() >= 1_000_000 {
        let mut ans = vec![];
        let mut sum = 0;
        for xi in x {
            let y = xi.min(1_000_000 - sum);
            ans.push(y.to_string());
            sum += y;
        }
        assert_eq!(sum, 1_000_000);
        println!("{}", ans.join(" "));
    } else {
        println!("IMPOSSIBLE");
    }
}