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
        let x = self.v[self.n].parse().unwrap();
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
    let mut a: Vec<Vec<u64>> = Vec::with_capacity(n);
    for _ in 0..n {
        a.push(r.nexts(n));
    }

    let mut dist = a.clone();
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                dist[i][j] = std::cmp::min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }

    let mut ans: u64 = 0;
    for i in 0..n {
        for j in (i+1)..n {
            if dist[i][j] < a[i][j] {
                println!("-1");
                return;
            }
            let mut used = true;
            for k in 0..n {
                if k == i || k == j { continue };
                if dist[i][j] == dist[i][k]+dist[k][j] {
                    used = false;
                }
            }
            if used {
                ans += dist[i][j];
            }
        }
    }
    println!("{}", ans);
}
