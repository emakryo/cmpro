#![allow(dead_code, unused_imports, unused_macros)]
use std::cmp::{max, min};
#[cfg(not(LOCAL))]
macro_rules! debug { ($($xs:expr),*) => () }
#[cfg(LOCAL)]
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
    let s: String = r.next();

    let mut ans = 0;
    for c in s.bytes() {
        if c.is_ascii_digit(){
            ans = ans * 10 + (c - '0' as u8) as u32;
        } else {
            println!("error");
            return;
        }
   }

    println!("{}", ans*2);
}
