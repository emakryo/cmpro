use std::io::stdin;
use std::cmp::min;

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
    let a: usize = r.next();
    let b: usize = r.next();

    if a + b > n + 1 || (a as u64) * (b  as u64) < (n as u64) {
        println!("-1");
        return;
    }

    let mut ans: Vec<usize> = Vec::new();
    let mut rem = n;
    let mut cum = 0;

    for i in 0..a {
        let m = min(b, rem - (a - i - 1));
        rem -= m;
        for j in (cum..(cum+m)).rev() {
            ans.push(j+1);
        }
        cum += m;
    }
    println!("{}", ans.iter().fold(String::new(), |mut x, y| {
        x.push_str(" ");
        x.push_str(&y.to_string());
        x
    }).trim());
}
