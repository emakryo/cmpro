#![allow(unused_macros, unused_imports)]

use proconio::marker::{Bytes, Chars};
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
        s: [Chars; 5],
    }

    let a = [
        ".###..#..###.###.#.#.###.###.###.###.###.",
        ".#.#.##....#...#.#.#.#...#.....#.#.#.#.#.",
        ".#.#..#..###.###.###.###.###...#.###.###.",
        ".#.#..#..#.....#...#...#.#.#...#.#.#...#.",
        ".###.###.###.###...#.###.###...#.###.###.",
    ].iter().map(|ai| ai.chars().collect::<Vec<_>>()).collect::<Vec<_>>();

    let mut ans = vec![];
    for i in 0..n {
        for j in 0..10 {
            let mut ok = true;
            for x in 0..4 {
                for y in 0..5 {
                    if a[y][4*j+x] != s[y][4*i+x] {
                        ok = false;
                    }
                }
            }
            if ok {
                ans.push((b'0' + j as u8) as char);
            }
        }
    }

    println!("{}", ans.into_iter().collect::<String>());
}