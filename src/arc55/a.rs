// #![feature(repeat_str)]
use std::io::stdin;
use std::iter;
use std::iter::FromIterator;

fn read_line() -> Vec<String> {
    let mut line = String::new();
    stdin().read_line(&mut line).expect("Failed to read line");
    return line.trim().split_whitespace().map(|s| s.to_string()).collect();
}

struct Reader {
    v: Vec<String>,
    n: usize,
}

impl Reader {
    fn new() -> Reader {
        let v = read_line();
        return Reader { v: v, n: 0 };
    }
    fn next<T>(&mut self) -> T where T: std::str::FromStr, T::Err: std::fmt::Debug {
        if self.n == self.v.len() {
            self.v = read_line();
            self.n = 0;
        }
        let x = self.v[self.n].parse().expect(&self.v[self.n]);
        self.n += 1;
        return x;
    }
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        let mut v = Vec::with_capacity(n);
        for _ in 0..n {
            v.push(self.next());
        }
        return v;
    }
}

fn main() {
    let mut r = Reader::new();
    let n: usize = r.next();
    println!("1{}7", String::from_iter(iter::repeat("0").take(n-1)));
}
