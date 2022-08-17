#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;
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
        println!("Case #{}: {}", i+1, solve_hard());
    }
}

fn gen_table(x: &[usize]) -> HashMap<Vec<usize>, usize> {
    let mut ret = HashMap::new();

    fn rec(table: &mut HashMap<Vec<usize>, usize>, x: Vec<usize>, y: &mut Vec<usize>, start: usize) -> usize {
        let mut ret = 0;
        if x.iter().all(|c| *c==0) {
            table.insert(y.clone(), start);
            return 1;
        }

        for (i, xi) in x.iter().enumerate() {
            if *xi > 0 {
                y.push(i);
                let mut xx = x.clone();
                xx[i] -= 1;
                ret += rec(table, xx, y, start + ret);
                y.pop();
            }
        }

        ret
    }

    let mut y = vec![];
    rec(&mut ret, x.to_owned(), &mut y, 0);

    ret
}

fn dist(s: &[usize], t: &[usize]) -> i64 {
    let mut k = 0;
    for i in 0..s.len().min(t.len()) {
        if s[i] != t[i] {
            break;
        }
        k = i + 1;
    }
    // dbg!(k);

    return (s.len() + t.len() - 2 * k) as i64;
}

pub fn dijkstra(s: usize, g: &Vec<Vec<(usize, i64)>>) -> Vec<i64> {
    let n = g.len();

    let inf = i64::max_value();
    let mut dist = vec![inf; n];
    dist[s] = 0;
    let mut que = std::collections::BinaryHeap::new();
    que.push((0, s));

    while let Some((d, u)) = que.pop() {
        let d = -d;
        if d > dist[u] {
            continue;
        }
        for &(v, w) in &g[u] {
            let d = d + w;
            if d < dist[v] {
                dist[v] = d;
                que.push((-d, v));
            }
        }
    }

    dist
}

fn solve_easy() -> i64 {
    input!{
        e: usize,
        w: usize,
        x: [[usize; w]; e],
    }

    let mut g = vec![vec![]; 2000 * (e + 2)];

    let mut m = gen_table(&x[0]);
    assert!(m.len() < 2000);

    for (s, j) in &m {
        g[0].push((2000 + j, dist(s, &[])));
    }

    for i in 0..e-1 {
        let nm = gen_table(&x[i+1]);
        assert!(nm.len() < 2000);

        for (s, j) in &m {
            for (t, k) in &nm {
                // dbg!(&s, &t);
                g[2000 * (i+1) + *j].push((2000 * (i+2) + *k, dist(s, t)));
            }
        }

        m = nm;
    }


    for (s, j) in &m {
        g[2000*e + j].push((2000*(e+1), dist(&[], s)));
    }

    let d = dijkstra(0, &g);

    d[2000*(e+1)]
}

fn solve_hard() -> i64 {
    input!{
        e: usize,
        w: usize,
        x: [[i64; w]; e],
    }

    let inf = 1_000_000_000;
    let mut dp1 = vec![vec![vec![inf; w]; e+1]; e];

    for i in 0..e {
        dp1[i][i+1] = x[i].clone();
        for j in 0..i {
            for k in 0..w {
                dp1[j][i+1][k] = dp1[j][i][k].min(x[i][k]);
            }
        }
    }

    let mut dp2 = vec![vec![inf; e+1]; e];

    for i in 0..e {
        for j in i+1..e+1 {
            dp2[i][j] = dp1[i][j].iter().sum();
        }
    }

    let mut dp3 = vec![vec![inf; e+1]; e];

    for i in 0..e {
        dp3[i][i+1] = 2 * dp2[i][i+1];
    }

    for i in 2..=e {
        for j in 0..=e-i {
            for k in j+1..j+i {
                dp3[j][j+i] = dp3[j][j+i].min(dp3[j][k] + dp3[k][j+i] - 2 * dp2[j][j+i]);
                // println!("{} {} {} {} {} {} {}", j, j+i, k, dp3[j][k], dp3[k][j+i], -2 * (dp2[j][k] + dp2[k][j+i] - dp2[j][j+i]), dp3[j][j+i]);
            }
        }
    }

    dp3[0][e]
}