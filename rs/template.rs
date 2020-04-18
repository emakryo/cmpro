#![allow(dead_code, unused_imports, unused_macros)]
use std::cmp::{max, min};
#[cfg(ONLINE_JUDGE)]
macro_rules! debug { ($($xs:expr),*) => () }
#[cfg(not(ONLINE_JUDGE))]
macro_rules! debug { ($($xs:expr),*) => { println!("{:?}", ($($xs),*))} }

fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}
struct Reader { v: Vec<String>, n: usize }
impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1; self.v[self.n-1].parse().ok().unwrap()
    }
    fn nexts<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.next()).collect()
    }
}

fn main() {
    let mut r = Reader::new();
    let n: usize = r.next();
    debug!(n, 2*n);
    println!("{}", n*2);
}
