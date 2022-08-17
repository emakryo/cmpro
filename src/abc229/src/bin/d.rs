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
        mut k : usize,
    }

    let mut j = 0;

    while j < s.len() && 0 < k {
        if s[j] == '.' {
            k -= 1;
        }
        j += 1;
    }

    while j < s.len() && s[j] == 'X' {
        j += 1;
    }

    let mut ans = j;

    for i in 0..s.len() {
        if j == s.len() {
            break;
        }

        if s[i] == '.' {
            j += 1;
            while j < s.len() && s[j] == 'X' {
                j += 1;
            }
        }

        ans = ans.max(j - i - 1);
    }

    println!("{}", ans);
}
