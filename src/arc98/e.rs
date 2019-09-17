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
    let k: usize = r.next();
    let q: usize = r.next();
    let a: Vec<i64> = r.nexts(n);

    let mut ai: Vec<(&i64, usize)> = a.iter().enumerate()
        .map(|(i, x)| (x, i)).collect();
    ai.sort();

    let mut ok: Vec<bool> = vec![true; n];
    let mut ans = 1e15_f64 as i64;
    for i in 0..n {
        let mut mins: Vec<i64> = Vec::new();
        let mut ms: Vec<i64> = Vec::new();
        for j in 0..n {
            if !ok[j] {
                if ms.len() >= k {
                    ms.sort();
                    mins.extend_from_slice(&ms[0..ms.len()-k+1]);
                }
                ms.clear();
            } else {
                ms.push(a[j]);
            }
        }
        if ms.len() >= k {
            ms.sort();
            mins.extend_from_slice(&ms[0..ms.len()-k+1]);
        }
        if mins.len() < q {
            break;
        }
        mins.sort();
        ans = std::cmp::min(ans, mins[q-1]-mins[0]);
        ok[ai[i].1] = false;
        //println!("{} {:?} {}", i, mins, ans);
    }

    println!("{:?}", ans);
}
