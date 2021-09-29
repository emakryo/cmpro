#![allow(unused_macros, unused_imports)]

use std::{collections::{BTreeSet, HashMap, HashSet}, iter::repeat};
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
        n: usize,
        l: usize,
    }

    fn rec(n: usize, l: usize) -> Vec<Vec<char>> {
        if l == 0 {
            return vec![];
        } else if l == 1 {
            return vec![
                vec!['0'],
                vec!['1'],
                vec!['2'],
            ];
        }

        let mut ret = vec![vec![]; 3*n];

        let mut k = 0;
        let mut x = 1;
        while 3 * x < 3 * n {
            k += 1;
            x *= 3;
        }
        dbg!(n, l, k, x, l as i32 - k as i32 -1);
        assert!(k <= l-1);

        for i in 0..n {
            ret[i].push('0');
            ret[i].extend(repeat('1').take(l-k-1));
            ret[i+n].push('1');
            ret[i+n].extend(repeat('2').take(l-k-1));
            ret[i+2*n].push('2');
            ret[i+2*n].extend(repeat('0').take(l-k-1));
        }

        let mut h = BTreeSet::new();
        let mut g = BTreeSet::new();
        for i in 0..x {
            let mut y = i;
            let mut s = vec![];
            for _ in 0..k {
                s.push(((y%3) as u8 + b'0') as char);
                y /= 3;
            }
            s.reverse();
            if i+2*n < 3*n {
                ret[i+2*n].extend(s.iter());
            } else {
                h.insert(s);
            }
        }

        let mut m = n - x / 3;

        if m > x / 3 {
            for i in 0..x {
                let mut y = i;
                let mut s = vec![];
                for _ in 0..k {
                    s.push(((y%3) as u8 + b'0') as char);
                    y /= 3;
                }
                s.reverse();
                // sub.push(s);
                // ret[(i+2*n+x)%(3*n)].extend(s.iter().rev());
                if h.contains(&s){
                    assert!(!g.contains(&s));
                    g.insert(s);
                } else {
                    h.insert(s);
                }
            }

            m -= x / 3;
        }
        dbg!(&h, &g);

        if m > 0 {
            let z = rec(m, k);
            dbg!(&z);
            for s in z {
                if h.contains(&s){
                    assert!(!g.contains(&s));
                    g.insert(s);
                } else {
                    h.insert(s);
                }
            }
        }

        dbg!(&h, &g);

        let mut a = g.iter().cloned().collect::<Vec<_>>();
        let mut b = g.iter().cloned().collect::<Vec<_>>();

        for s in &g {
            h.remove(s);
        }

        for s in h {
            if a.len() <= b.len() {
                a.push(s);
            } else {
                b.push(s);
            }
        }

        for (i, s) in a.into_iter().enumerate() {
            ret[i].extend(s.iter());
        }

        for (i, s) in b.into_iter().enumerate() {
            ret[i + n].extend(s.iter());
        }


        ret
    }

    let ans = rec(n, l);
    // let mut h = HashSet::new();
    for s in ans {
        assert_eq!(s.len(), l);
        let s = s.into_iter().collect::<String>();
        // assert!(!h.contains(&s));
        println!("{}", s);
        // h.insert(s);
    }
}

