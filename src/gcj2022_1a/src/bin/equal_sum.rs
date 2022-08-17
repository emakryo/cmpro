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
    use std::{cell::RefCell, io::Read, rc::Rc};
    thread_local!(pub static SCANNER: Rc<RefCell<Scanner>> = Rc::new(RefCell::new(Scanner::default())));

    #[macro_export]
    macro_rules! input{
        (read=$read:expr,$($r:tt)*)=>{
            let sc = input::SCANNER.with(|x| {
                *x.borrow_mut() = input::Scanner::new($read);
                std::rc::Rc::clone(x)
            });
            input_inner!{sc.borrow_mut(),$($r)*}
        };
        ($($r:tt)*)=>{
            let sc = input::SCANNER.with(|x| std::rc::Rc::clone(x));
            input_inner!{sc.borrow_mut(),$($r)*}
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
    input!{
        read=input::stdin(false),
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn query(a: &[usize]) -> Vec<usize> {
    for ai in a[..a.len()-1].iter() {
        print!("{} ", *ai);
    }
    println!("{}", a[a.len()-1]);

    input!{
        b: [usize; a.len()]
    }
    b
}

fn solve() {
    input! {
        n: usize,
    }
    let mut a = (0..30).rev().map(|x| 1<<x).collect::<Vec<_>>();
    for i in 0..(n-a.len()) {
        a.push(1_000_000_000-i);
    }
    a.sort();
    a.reverse();

    assert!(a.iter().all(|&x| x <= 1_000_000_000));

    let b = query(&a);

    let s = a.iter().sum::<usize>() + b.iter().sum::<usize>();
    let mut t = 0;

    let mut ans = vec![];

    for bi in b {
        if t + bi <= s / 2 {
            t += bi;
            ans.push(bi);
        }
    }

    for ai in a {
        if t + ai <= s / 2 {
            t += ai;
            ans.push(ai);
        }
    }

    assert_eq!(t, s / 2);

    for x in ans[..ans.len()-1].iter() {
        print!("{} ", *x);
    }
    println!("{}", ans[ans.len()-1]);
}
