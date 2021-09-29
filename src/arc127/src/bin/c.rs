#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;

use proconio::marker::Bytes;
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
        x: Bytes,
    }

    let mut rs = BTreeMap::new();

    for (i, &b) in x.iter().enumerate() {
        if b == b'1' {
            rs.insert(i + n - x.len(), 1);
        }
    }

    let mut ans = String::from("1");
    for i in 0..n {
        dbg!(&rs);
        let p = *rs.iter().next().unwrap().0;
        if rs.len() == 1 && p == n-1 {
            println!("{}", ans);
            return;
        }

        if rs.get(&i) == None || (rs.len()==1 && rs.get(&i) == Some(&1)) {
            ans.push('0');
            let (&p, &c) = rs.iter().rev().next().unwrap();

            if c == 1 {
                rs.remove(&p);
            } else {
                *rs.get_mut(&p).unwrap() -= 1;
            }
            if p+c-1 < n-1 {
                rs.insert(p+c, n-1-(p+c-1));
            }
        } else {
            ans.push('1');

            let c = rs.remove(&i).unwrap();
            if c > 1 {
                rs.insert(i+1, c-1);
            }
        }
    }
}