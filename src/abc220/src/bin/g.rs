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

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
struct Rat(i64, i64);  // denominator, nominator

fn gcd(x: i64, y: i64) -> i64 {
    if y == 0 { x }
    else { gcd(y, x%y) }
}

impl Rat {
    fn new(denom: i64, nom: i64) -> Self {
        if denom == 0 {
            Self(0, 1)
        } else if nom == 0 {
            Self(1, 0)
        }else {
           let g = gcd(denom.abs(), nom.abs());
           if nom < 0 {
               Self(-denom / g, -nom / g)
           } else {
               Self(denom / g, nom / g)
           }
        }
    }

    fn neg(mut self) -> Self {
        self.0 = -self.0;
        self
    }

    fn reciprocal(self) -> Self {
        Self(self.1, self.0)
    }

    fn add(&self, other: &Self) -> Self {
        Rat::new(self.0*other.1+self.1*other.0, self.1 * other.1)
    }

    fn sub(&self, other: &Self) -> Self {
        self.add(&other.neg())
    }

    fn mul(&self, other: &Self) -> Self {
        Rat::new(self.0 * other.0, self.1 * other.1)
    }

    fn is_inf(&self) -> bool {
        self.1 == 0
    }

    fn to_f64(&self) -> Option<f64> {
        if self.1 == 0 {
            None
        } else {
            Some(self.0 as f64 / self.1 as f64)
        }
    }
}

fn main() {
    proconio::input!{
        n: usize,
        ps: [(i64, i64, i64); n],
    }

    let mut hm = HashMap::<(Rat, Rat), HashMap<Rat, i64>>::new();

    for i in 0..n {
        for j in i+1..n {
            let a = Rat::new(ps[i].1-ps[j].1, ps[i].0-ps[j].0);
            let x = Rat::new(ps[i].0+ps[j].0, 2);
            let y = Rat::new(ps[i].1+ps[j].1, 2);
            let ra = a.neg().reciprocal();

            let b = y.sub(&ra.mul(&x));

            let k = if ra.is_inf() {
                (a, x)
            } else {
                (a, b)
            }; 
            dbg!(i, j, k);
            let v = ps[i].2 + ps[j].2;
            let g = hm.entry(k).or_insert(HashMap::new());

            let k2 = if a.is_inf() {
                x
            } else {
                y.sub(&a.mul(&x))
            };
            let u = g.get_mut(&k2);
            if let Some(u) = u {
                let t = (*u).max(v);
                *u = t;
            } else {
                g.insert(k2, v);
            }
        }
    }

    let mut ans = 0;

    for (k, vs) in &hm {
        // dbg!(k, &vs);
        let mut xs = vs.values().cloned().collect::<Vec<_>>();
        xs.sort();
        xs.reverse();

        if xs.len() >= 2 {
            ans = ans.max(xs[0] + xs[1]);
        }
    }

    if ans == 0 {
        println!("-1");
    } else {
        println!("{}", ans);
    }
}