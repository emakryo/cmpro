use std::io::stdin;

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

fn gcd(x: u64, y: u64) -> u64 {
    if y==0 {
        return x;
    } else {
        return gcd(y, x%y);
    }
}

fn main() {
    let mut r = Reader::new();
    let t: usize = r.next();
    for _ in 0..t {
        let a: u64 = r.next();
        let b: u64 = r.next();
        let c: u64 = r.next();
        let d: u64 = r.next();
        if a < b {
            println!("No");
            continue;
        }
        if d < b {
            println!("No");
            continue;
        }
        if c >= b {
            println!("Yes");
            continue;
        }

        let a = a % b;
        let d = d % b;
        
        let g = gcd(d, b);
        let k = (b - a - 1) / g;
        if a + k * g <= c {
            println!("Yes");
        } else {
            println!("No");
        }
    }
}
