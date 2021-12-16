#![allow(unused_macros, unused_imports)]

use std::mem::swap;

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

fn p(s: &Vec<Vec<u8>>) {
    println!("[");
    for si in s {
        println!("{}", si.iter().map(ToString::to_string).collect::<Vec<_>>().join(""));
    }
    println!("]");
}

fn main() {
    proconio::input!{
        n: usize,
        s: [Bytes; n],
    }
    let mut s = s
        .into_iter()
        .map(|t| t.into_iter().map(|c| c-b'0').collect::<Vec<_>>())
        .collect::<Vec<_>>();
    
    for i in 0..n-1 {
        let mut k = None;
        for j in i..n {
            if s[i][j] == 1 {
                k = Some(j);
            }
        }
        if k.is_none() {
            println!("Even");
            return;
        }
        let k = k.unwrap();

        for j in 0..n {
            s[j].swap(k, i);
        }
        // p(&s);
        for j in i+1..n {
            if s[i][j] == 1 {
                for k in 0..n {
                    s[k][j] ^= s[k][i];
                }
            }
        }
        // p(&s);
    }

    if s[n-1][n-1] == 1 {
        println!("Odd")
    } else {
        println!("Even");
    }
}