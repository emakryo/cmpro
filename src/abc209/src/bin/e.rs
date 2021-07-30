#![allow(unused_macros, unused_imports)]
use std::collections::VecDeque;

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
        s: [Bytes; n],
    }

    let m = 53*53*53;
    let mut g = vec![vec![]; m];
    let mut rg = vec![vec![]; m];
    let mut es = vec![];

    fn encode(xs: &[u8]) -> usize {
        xs.iter().take(3).map(|x| match *x {
            x if b'a' <= x && x <= b'z' => x - b'a',
            x if b'A' <= x && x <= b'Z' => x - b'A' + 26,
            _ => unreachable!(),
        } as usize).fold(0, |x, y| x * 52 + y)
    }

    for si in &s {
        let a = encode(&si[..3]);
        let b = encode(&si[si.len()-3..]);
        g[a].push(b);
        rg[b].push(a);
        es.push((a, b));
    };

    let mut to_win = vec![0; m];

    #[derive(Clone, Copy, PartialEq, Eq)]
    enum State {
        Win,
        Lose,
        Draw,
    }
    let mut state = vec![State::Draw; m];

    let mut que = VecDeque::new();

    for (i, us) in g.iter().enumerate() {
        if us.len() == 0 {
            state[i] = State::Win;
            que.push_back(i);
        }
    }
    while let Some(u) = que.pop_front() {
        for &v in &rg[u] {
            if state[v] == State::Win || state[v] == State::Lose {
                continue;
            }
            if state[u] == State::Lose {
                to_win[v] += 1;
                if to_win[v] == g[v].len() {
                    state[v] = State::Win;
                    que.push_back(v)
                }
            } else if state[u] == State::Win {
                state[v] = State::Lose;
                que.push_back(v);
            }
        }
    }

    for (_, b) in es {
        match &state[b] {
            State::Win => println!("Takahashi"),
            State::Lose => println!("Aoki"),
            State::Draw => println!("Draw"),
        }
    }
}