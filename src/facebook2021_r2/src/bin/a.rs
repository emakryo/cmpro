#![allow(unused_macros, unused_imports)]

use std::{collections::{BTreeMap, HashMap, HashSet}, hash::Hash, iter::FromIterator};
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn main() {
    proconio::input!{
        t: usize,
    }

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        m: usize,
        s: [usize; m],
        p: [[usize; m]; n],
    }

    let mut x = s;
    let mut y = vec![];

    let mut ans = 0;
    for pi in p {
        let mut nx = vec![];
        let mut ny = vec![];
        let mut pi = MultiBTreeSet::from_iter(pi.into_iter());
        // dbg!(&x, &y);

        for yi in y.iter() {
            if pi.contains(yi) {
                pi.remove(yi);
                ny.push(*yi);
            } else {
                ans += 1;
            }
        }

        for xi in x.iter() {
            if pi.contains(xi) {
                pi.remove(xi);
                nx.push(*xi);
            }
        }

        for z in pi.to_vec() {
            ny.push(*z);
        }

        x = nx;
        y = ny;
    }

    println!("{}", ans);
}

struct MultiBTreeSet<T>(BTreeMap<T, usize>, usize);


impl<T: Eq + Ord> MultiBTreeSet<T> {
    fn new() -> Self {
        Self(BTreeMap::new(), 0)
    }

    fn insert(&mut self, x: T) -> usize {
        let c = self.0.entry(x).or_insert(0);
        *c += 1;
        self.1 += 1;
        *c
    }

    fn remove(&mut self, x: &T) -> bool {
        let c = self.0.get_mut(x);
        if let Some(c) = c {
            *c -= 1;
            self.1 -= 1;
            if *c == 0 {
                self.0.remove(x);
            }
            true
        } else {
            false
        }
    }

    fn contains(&self, x: &T) -> bool {
        self.0.contains_key(x)
    }

    fn len(&self) -> usize {
        self.1
    }

    fn to_vec(&self) -> Vec<&T> {
        let mut v = Vec::with_capacity(self.1);
        for (x, n) in &self.0 {
            for _ in 0..*n {
                v.push(x);
            }
        }

        v
    }
}

impl<T: Eq + Ord> FromIterator<T> for MultiBTreeSet<T> {
    fn from_iter<I: IntoIterator<Item=T>>(iter: I) -> Self {
        let mut x = Self::new();
        for i in iter {
            x.insert(i);
        }

        x
    }
}