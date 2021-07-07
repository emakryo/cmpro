use std::{fmt::Display, time::{Duration, Instant}, usize};
use itertools::Itertools;

#[proconio::fastout]
fn main() {
    let start = Instant::now();
    proconio::input! {
        (n, m): (usize, usize),
        mut s: [String; m],
    }

    s.sort_by_key(|x| x.len());
    s.reverse();

    let mut t: Vec<String> = vec![];
    for x in s {
        let mut add = true;
        for y in &t {
            if y.contains(&x) {
                add = false;
            }
        }
        if add {
            t.push(x);
        }
    }
    // dbg!(&t);

    let t = t.into_iter().map(Vec::from).collect::<Vec<_>>();

    let mut st = State::new(n, t);

    st.search(&start);
    st.set_best();
    println!("{}", st);
    dbg!(st.score());
}

#[derive(Debug)]
struct State {
    side: usize,
    board: Vec<u8>,
    history: Vec<Trans>,
    inputs: Vec<Vec<u8>>,
    used: Vec<bool>,
    last: Vec<i32>,
    best: Vec<Trans>,
    best_score: u64,
}

#[derive(Debug, Clone, Copy)]
struct Trans{
    pos: (usize, usize),
    index: usize,
    dir: Dir,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Dir {
    Vert,
    Horz,
}

impl Display for State {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for line in &self.board.iter().chunks(self.side) {
            writeln!(f, "{}", line.map(|x| char::from(*x)).collect::<String>())?;
        }
        Ok(())
    }
}

impl State {
    fn new(side: usize, inputs: Vec<Vec<u8>>) -> Self {
        State{
            side,
            board: vec![b'.'; side*side],
            last: vec![-1; side*side],
            history: vec![],
            used: vec![false; inputs.len()],
            inputs,
            best: vec![],
            best_score: 0,
        }
    }

    fn push(&mut self, trans: Trans) -> Result<(), ()> {
        if self.used[trans.index] {
            return Err(());
        }
        let s = &self.inputs[trans.index];
        if trans.dir == Dir::Vert {
            for (i, c) in s.iter().enumerate() {
                let x = (trans.pos.0 + i) % self.side;
                let y = trans.pos.1 % self.side;
                let j = x*self.side+y;
                if &self.board[j] != c && &self.board[j] != &b'.' {
                    return Err(())
                }
            }
        } else {
            for (i, c) in s.iter().enumerate() {
                let x = trans.pos.0 % self.side;
                let y = (trans.pos.1 + i) % self.side;
                let j = x*self.side+y;
                if &self.board[j] != c && &self.board[j] != &b'.' {
                    return Err(())
                }
            }
        }
        let k = self.history.len();
        self.history.push(trans);
        if trans.dir == Dir::Vert {
            for (i, c) in s.iter().enumerate() {
                let x = (trans.pos.0 + i) % self.side;
                let y = trans.pos.1 % self.side;
                let j = x*self.side+y;
                if self.last[j] < 0 {
                    self.last[j] = k as i32;
                }
                self.board[j] = *c;
            }
        } else {
            for (i, c) in s.iter().enumerate() {
                let x = trans.pos.0 % self.side;
                let y = (trans.pos.1 + i) % self.side;
                let j = x*self.side+y;
                if self.last[j] < 0 {
                    self.last[j] = k as i32;
                }
                self.board[j] = *c;
            }
        }
        self.used[trans.index] = true;

        Ok(())
    }

    fn pop(&mut self) -> Option<Trans> {
        if let Some(trans) = self.history.pop() {
            let k = self.history.len();
            let s = &self.inputs[trans.index];
            if trans.dir == Dir::Vert {
                for (i, _) in s.iter().enumerate() {
                    let x = (trans.pos.0 + i) % self.side;
                    let y = trans.pos.1 % self.side;
                    let j = x*self.side+y;
                    if self.last[j] == k as i32 {
                        self.last[j] = -1;
                        self.board[j] = b'.';
                    }
                }
            } else {
                for (i, _) in s.iter().enumerate() {
                    let x = trans.pos.0 % self.side;
                    let y = (trans.pos.1 + i)% self.side;
                    let j = x*self.side+y;
                    if self.last[j] == k as i32 {
                        self.last[j] = -1;
                        self.board[j] = b'.';
                    }
                }
            }
            self.used[trans.index] = false;

            Some(trans)
        } else {
            None
        }
    }

    fn score(&self) -> u64 {
        (if self.history.len() == self.inputs.len() {
            let n = self.side as f64;
            let d = self.board.iter().filter(|x| **x==b'.').count() as f64;
            1e8 * 2.0*n*n / (2.0*n*n - d)
        } else {
            let c = self.history.len() as f64;
            let m = self.inputs.len() as f64;
            1e8 * c / m
        }) as u64
    }

    fn search(&mut self, start: &Instant) {
        self.dfs(0, start);
    }

    fn dfs(&mut self, i: usize, start: &Instant) {
        if Instant::now() - *start >= Duration::from_millis(2950) {
            return;
        }
        if i >= self.inputs.len() {
            return;
        }
        for p in 0..(self.side*self.side) {
            if let Ok(_) = self.push(Trans{
                pos: (p/self.side, p%self.side),
                index: i,
                dir: if i%2 == 0 {
                    Dir::Vert
                } else {
                    Dir::Horz
                }
            }) {
                let score = self.score();
                if score >= self.best_score {
                    self.best_score = score;
                    self.best = self.history.clone();
                }
                self.dfs(i+1, start);
                self.pop();
            }
        }
        self.dfs(i+1, start);
    }

    fn set_best(&mut self) {
        while self.history.len() > 0 {
            self.pop();
        }
        for trans in self.best.clone() {
            self.push(trans).unwrap();
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_output() {
        let mut s = State::new(20, vec![Vec::from("abc")]);
        s.push(Trans {
            pos: (0, 0),
            index: 0,
            dir: Dir::Horz,
        }).unwrap();
        println!("{}", s);
        s.pop();
        println!("{}", s);
    }

}