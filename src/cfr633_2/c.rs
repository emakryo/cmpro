#![allow(dead_code)]
fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}
struct Reader { v: Vec<String>, n: usize }
impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    fn next<T>(&mut self) -> T where T: std::str::FromStr, T::Err: std::fmt::Debug {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1; self.v[self.n-1].parse().expect(&self.v[self.n-1])
    }
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        let mut v = Vec::with_capacity(n); for _ in 0..n { v.push(self.next()); } v
    }
}

type Val = i64;
type Laz = i64;

struct LazySegTree {
    node_v: Vec<Val>,
    node_l: Vec<Laz>,
    def_v: Val,
    def_l: Laz,
}

use std::cmp::min;
impl LazySegTree {
    fn merge(x: Val, y: Val) -> Val {
        min(x, y)
    }
    fn apply(x: Val, a: Laz) -> Val {
        x+a
    }
    fn spread(a: Laz, b: Laz) -> Laz {
        a+b
    }
    fn new(n: usize, def_v: Val, def_l: Laz) -> Self {
        let mut n_ = 1;
        while n_ < n { n_ *= 2 };
        n_ *= 2;
        let node_v = vec![def_v; n_];
        let node_l = vec![def_l; n_];
        Self { node_v, node_l, def_v, def_l }
    }
    fn from_slice(vs: &[Val], def_v: Val, def_l: Laz) -> Self {
        let mut st = Self::new(vs.len(), def_v, def_l);
        let n = st.node_v.len();
        for i in 0..vs.len() {
            st.node_v[(n<<1)+i] = vs[i];
        }
        for i in (1..n<<1).rev() {
            st.node_v[i] = Self::merge(st.node_v[i*2], st.node_v[i*2+1]);
        }
        st
    }
    fn query(&mut self, a: usize, b: usize) -> Val {
        let n = self.node_v.len();
        self.q(1, 0, n<<1, a, b)
    }
    fn q(&mut self, i: usize, s: usize, t: usize, a: usize, b: usize) -> Val {
        if t <= a || b <= s {
            self.def_v
        } else if a <= s && t <= b {
            self.eval(i)
        } else {
            Self::merge(self.q(i*2, s, (s+t)/2, a, b), self.q(i*2+1, (s+t)/2, t, a, b))
        }
    }
    fn eval(&mut self, i: usize) -> Val {
        self.node_v[i] = Self::apply(self.node_v[i], self.node_l[i]);
        self.node_l[i*2] = Self::spread(self.node_l[i*2], self.node_l[i]);
        self.node_l[i*2+1] = Self::spread(self.node_l[i*2+1], self.node_l[i]);
        self.node_l[i] = self.def_l;
        self.node_v[i]
    }
    fn update(&mut self, a: usize, b: usize, x: Laz) {
        let n = self.node_v.len();
        self.u(1, 0, n<<1, a, b, x);
    }
    fn u(&mut self, i: usize, s: usize, t: usize, a: usize, b: usize, x: Laz) {
        if s <= a || b <= t {
            return;
        } else if a <= s && t <= b {
            self.node_l[i] = Self::spread(self.node_l[i], x);
        } else {
            self.u(i*2, s, (s+t)/2, a, b, x);
            self.u(i*2+1, (s+t)/2, t, a, b, x);
        }
    }
}


use std::cmp::max;
fn main() {
    let mut r = Reader::new();
    let t: usize = r.next();
    for _ in 0..t {
        solve(&mut r);
    }
}

fn solve(r: &mut Reader) {
    let n: usize = r.next();
    let mut a: Vec<i64> = vec![];
    for _ in 0..n {
        a.push(r.next());
    }

    let diff_or = a.iter().scan(-1e15 as i64, |st, x| {
        *st = max(*st, *x);
        Some(*st)
    }).zip(&a).fold(0, |z, (x, y)| {
        z | x-y
    });

    println!("{}", 64-diff_or.leading_zeros());

}
