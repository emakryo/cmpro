#![allow(unused_macros, unused_imports)]

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

    let mut ans = 0;
    let n = s.len();
    for (a, b) in s.iter().take(n/2).zip(s.iter().rev().take(n/2)) {
        ans += match (&a, &b) {
            ('i', 'i') | ('w', 'w') | ('(', ')') | (')', '(') => 0,
            _ => 1,
        };
    }
    if n%2 == 1 && (s[n/2] == ')' ||s[n/2] == '(') {
        ans += 1;
    }

    println!("{}", ans);
}