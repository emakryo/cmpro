#![allow(unused_macros)]

use std::collections::VecDeque;
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        s: proconio::marker::Bytes,
    }

    let mut deq = VecDeque::new();

    for i in 0..n {
        match s[i] {
            b'A' if deq.len() >= 1 => {
                println!("{}", deq.pop_front().unwrap());
            }
            b'B' if deq.len() >= 2 => {
                let x = deq.pop_front().unwrap();
                println!("{}", deq.pop_front().unwrap());
                deq.push_front(x);
            }
            b'C' if deq.len() >= 3 => {
                let x = deq.pop_front().unwrap();
                let y = deq.pop_front().unwrap();
                println!("{}", deq.pop_front().unwrap());
                deq.push_front(y);
                deq.push_front(x);
            }
            b'D' if deq.len() >= 1 => {
                println!("{}", deq.pop_back().unwrap());
            }
            b'E' if deq.len() >= 2 => {
                let x = deq.pop_back().unwrap();
                println!("{}", deq.pop_back().unwrap());
                deq.push_back(x);
            }
            b'F' if deq.len() >= 3 => {
                let x = deq.pop_back().unwrap();
                let y = deq.pop_back().unwrap();
                println!("{}", deq.pop_back().unwrap());
                deq.push_back(y);
                deq.push_back(x);
            }
            b'A'..=b'F' => println!("ERROR"),
            b'L' => deq.push_front(i+1),
            b'R' => deq.push_back(i+1),
            _ => ()
        };
    }
}