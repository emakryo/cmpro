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
        r: usize,
        c: usize,
        p: [Chars; r],
    }

    let mut visit = vec![vec![vec![vec![false; 4]; 16]; c]; r];
    let mut que = VecDeque::new();
    que.push_back((0, 0, 0, 0));

    while let Some((x, y, m, d)) = que.pop_front() {
        dbg!(x, y, m, d);
        if visit[x][y][m][d] { continue }
        visit[x][y][m][d] = true;
        match p[x][y] {
            '<' => que.push_back((x, (y+c-1)%c, m, 1)),
            '>' => que.push_back((x, (y+1)%c, m, 0)),
            '^' => que.push_back(((x+r-1)%r, y, m, 2)),
            'v' => que.push_back(((x+1)%r, y, m, 3)),
            '_' => if m == 0 {
                que.push_back((x, (y+1)%c, m, 0));
            } else {
                que.push_back((x, (y+c-1)%c, m, 1));
            },
            '|' => if m == 0 {
                que.push_back(((x+1)%r, y, m, 3));
            } else {
                que.push_back(((x+r-1)%r, y, m, 2));
            },
            '?' => {
                que.push_back((x, (y+c-1)%c, m, 1));
                que.push_back((x, (y+1)%c, m, 0));
                que.push_back(((x+r-1)%r, y, m, 2));
                que.push_back(((x+1)%r, y, m, 3));
            },
            '.' => match d {
                1 => que.push_back((x, (y+c-1)%c, m, 1)),
                0 => que.push_back((x, (y+1)%c, m, 0)),
                2 => que.push_back(((x+r-1)%r, y, m, 2)),
                3 => que.push_back(((x+1)%r, y, m, 3)),
                _ => panic!(),
            },
            '@' => {
                println!("YES");
                return;
            },
            v @ ('0'..='9') => {
                let v = (v as u8 - b'0') as usize;
                match d {
                    1 => que.push_back((x, (y+c-1)%c, v, 1)),
                    0 => que.push_back((x, (y+1)%c, v, 0)),
                    2 => que.push_back(((x+r-1)%r, y, v, 2)),
                    3 => que.push_back(((x+1)%r, y, v, 3)),
                    _ => panic!(),
                }
            },
            '+' => {
                let v = (m + 1) % 16;
                match d {
                    1 => que.push_back((x, (y+c-1)%c, v, 1)),
                    0 => que.push_back((x, (y+1)%c, v, 0)),
                    2 => que.push_back(((x+r-1)%r, y, v, 2)),
                    3 => que.push_back(((x+1)%r, y, v, 3)),
                    _ => panic!(),
                }
            }
            '-' => {
                let v = (m + 15) % 16;
                match d {
                    1 => que.push_back((x, (y+c-1)%c, v, 1)),
                    0 => que.push_back((x, (y+1)%c, v, 0)),
                    2 => que.push_back(((x+r-1)%r, y, v, 2)),
                    3 => que.push_back(((x+1)%r, y, v, 3)),
                    _ => panic!(),
                }
            },
            _ => panic!(),
        }
    }

    println!("NO");
}