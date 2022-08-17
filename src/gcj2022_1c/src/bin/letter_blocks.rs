#![allow(unused_macros, unused_imports)]

use std::iter::FromIterator;
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
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        if let Some(x) = solve() {
            println!("{}", x);
        } else {
            println!("IMPOSSIBLE");
        }
    }
}

fn solve() -> Option<String> {
    input! {
        n: usize,
        s: [Bytes; n],
    }

    let c = 26;
    let mut t = vec![(None, None); c];
    let mut u = vec![0; c];

    for (i, si) in s.iter().enumerate() {
        if si.iter().all(|x| x == &si[0]) {
            u[(si[0] - b'A') as usize] += si.len();
        } else {
            let a = (si[0] - b'A') as usize;
            let b = (*si.last().unwrap() - b'A') as usize;
            if t[a].1.is_some() || t[b].0.is_some() {
                return None;
            }
            t[a].1 = Some(i);
            t[b].0 = Some(i);
        }
    }

    let mut k = None;
    let mut ans: Vec<u8> = vec![];
    while !t.is_empty() {
        // dbg!(&t);
        let mut ok = false;
        for i in 0..t.len() {
            if t[i].0.is_none() && t[i].1.is_none() {
                t.remove(i);
                ok = true;
                break;
            } else if k == t[i].0 {
                ok = true;
                if t[i].1.is_some() {
                    k = t[i].1;
                    let a = s[k.unwrap()][0];
                    ans.extend(std::iter::repeat(a).take(u[(a-b'A') as usize]));
                    u[(a-b'A') as usize] = 0;
                    ans.extend(s[k.unwrap()].iter());
                    t.remove(i);
                    break;
                } else {
                    let a = *s[k.unwrap()].last().unwrap();
                    ans.extend(std::iter::repeat(a).take(u[(a-b'A') as usize]));
                    u[(a-b'A') as usize] = 0;
                    k = None;
                    t.remove(i);
                    break;
                }
            }
        }
        if !ok {
            return None;
        }
    }

    for (i, &ui) in u.iter().enumerate() {
        if ui > 0 {
            ans.extend(std::iter::repeat(i as u8 + b'A').take(ui));
        }
    }

    let mut f = vec![false; c];

    for i in 0..ans.len()-1 {
        if ans[i] != ans[i+1] {
            if f[(ans[i+1] - b'A') as usize] {
                return None;
            }
            f[(ans[i] - b'A') as usize] = true;
        }
    }
    if f[(*ans.last().unwrap() - b'A') as usize] {
        return None;
    }

    Some(String::from_iter(ans.into_iter().map(|c| c as char)))
}