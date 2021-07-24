#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;

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
        mut s: [Chars; n],
    }

    let mut ans = 0;

    for i in 0..n {
        for j in 0..m {
            if s[i][j] == '.' {
                continue;
            }

            s[i][j] = '.';

            let mut que = VecDeque::new();
            let mut visit = vec![vec![false; m]; n];
            que.push_back((i as i32, j as i32));
            while let Some((x, y)) = que.pop_front() {
                let dx = [0, 1, 0, -1];
                let dy = [1, 0, -1, 0];
                if visit[x as usize][y as usize] {
                    continue;
                }
                visit[x as usize][y as usize] = true;

                for k in 0..4 {
                    let x = x + dx[k];
                    let y = y + dy[k];
                    if 0 <= x && x < n as i32 && 0 <= y && y < m as i32 &&
                        s[x as usize][y as usize] == '.' && !visit[x as usize][y as usize] {
                        que.push_back((x, y));
                    }

                }
            }

            let mut ok = true;
            for x in 0..n {
                for y in 0..m {
                    if s[x][y] == '.' && !visit[x][y] {
                        ok = false;
                    }
                }
            }

            if ok {
                ans += 1;
            }

            s[i][j] = '#';
        }
    }

    println!("{}", ans);
}