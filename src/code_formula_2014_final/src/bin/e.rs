#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;

use proconio::marker::Chars;
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
        s: Chars,
    }

    if s.len() == 1 {
        println!("{} 0", if s[0] == 'b' { 1 } else { 2 });
        return;
    }

    let mut fib = vec![1, 1];
    for i in 2..30 {
        fib.push(fib[i-1]+fib[i-2]);
    }

    let n = fib.iter().enumerate().find_map(|(i, x)| if *x == s.len() { Some(i) } else { None }).unwrap();

    fn check(n: usize, k: usize, s: &[char], fib: &[usize]) -> bool {
        // dbg!(n, k, s);
        if n == 0 {
            s[0] == 'b'
        } else if n == 1 {
            s[0] == 'a'
        } else {
            if k%2 == 0 {
                check(n-1, k/2, &s[..fib[n-1]], fib) && check(n-2, k/4, &s[fib[n-1]..], fib)
            } else{
                check(n-2, k/4, &s[..fib[n-2]], fib) && check(n-1, k/2, &s[fib[n-2]..], fib)
            }
        }
    }

    for k in 0..1<<(n-1) {
        if check(n, k, &s, &fib) {
            println!("{} {}", n+1, k);
            return;
        }
    }
}