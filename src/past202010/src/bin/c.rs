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
        n: usize,
        m: usize,
        s: [Chars; n],
    }

    let mut ans = vec![String::new(); n];

    for i in 0..n as i32 {
        for j in 0..m as i32 {
            let dx = [-1, -1, -1, 0, 0, 0, 1, 1, 1];
            let dy = [-1, 0, 1, -1, 0, 1, -1, 0, 1];

            let mut c = 0;
            for k in 0..9 {
                let x = i + dx[k];
                let y = j + dy[k];

                if 0 <= x && x < n as i32 && 0 <= y && y < m as i32 {
                    if s[x as usize][y as usize] == '#' {
                        c += 1;
                    }
                }
            }

            ans[i as usize].extend(c.to_string().chars());
        }
        println!("{}", ans[i as usize]);
    }

}