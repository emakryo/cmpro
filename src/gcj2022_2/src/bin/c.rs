#![allow(unused_macros, unused_imports)]

use std::mem::swap;
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
                Rc::clone(x)
            })
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
        ($sc:expr,($($t:tt),*))=>{($({read_value!($sc,$t)}),*)};
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
        ($sc:expr,$t:ty)=>{{
            let mut sc = $sc;
            sc.next::<$t>()
        }};
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
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    input!{
        n: usize,
        ps: [(i64, i64); n],
        qs: [(i64, i64); n+1],
    }

    let mut d = vec![vec![(0, 0); n+1]; n];

    for i in 0..n {
        for j in 0..n+1 {
            d[i][j] = (-dist(ps[i], qs[j]), j);
        }

        d[i].sort();
        d[i].reverse();
    }
    let mut ans = vec![];
    if rec(n, 0, 0, &d, &mut ans) {
        println!("POSSIBLE");
        for (a, b) in ans {
            println!("{} {}", a, b);
        }
    } else {
        println!("IMPOSSIBLE");
    }

}

fn dist(x: (i64, i64), y: (i64, i64)) -> i64 {
    (x.0-y.0).pow(2) + (x.1 - y.1).pow(2)
}

fn rec(n: usize, mut s: usize, mut t: usize, d: &Vec<Vec<(i64, usize)>>, ans: &mut Vec<(usize, usize)>) -> bool {
    if ans.len() == n {
        return true;
    }

    for i in 0..n {
        if s >> i & 1 == 1 {
            continue;
        }

        let mut k = 0;
        for j in 0..n {
            if t >> d[i][j].1 & 1 == 1 {
                continue;
            }

            k = d[i][j].1;
            break;
        }

        if k != 0 {
            s += 1 << i;
            t += 1 << k;
            ans.push((i+1, k+1));

            if rec(n, s, t, d, ans) {
                return true;
            }

            ans.pop();
            t -= 1 << k;
            s -= 1 << i;
        }
    }

    return false;
}