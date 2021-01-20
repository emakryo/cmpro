use std::collections::VecDeque;
use std::io::BufRead;

fn play(s1: &[usize], s2: &[usize]) -> (usize, VecDeque<usize>) {
    // dbg!(s1);
    // dbg!(s2);
    let mut p1: VecDeque<usize> = s1.iter().cloned().collect();
    let mut p2: VecDeque<usize> = s2.iter().cloned().collect();

    let mut c = 0;
    while p1.len() > 0 && p2.len() > 0 {
        c += 1;
        if c > 100000 {
            return (0, p1);
        }
        // dbg!(&p1);
        // dbg!(&p2);
        let x1 = p1.pop_front().unwrap();
        let x2 = p2.pop_front().unwrap();

        if x1 <= p1.len() && x2 <= p2.len() {
            if play(&p1.make_contiguous()[..x1], &p2.make_contiguous()[..x2]).0 == 0 {
                p1.push_back(x1);
                p1.push_back(x2);
            } else {
                p2.push_back(x2);
                p2.push_back(x1);
            }
        } else if x1 < x2 {
            p2.push_back(x2);
            p2.push_back(x1);
        } else {
            p1.push_back(x1);
            p1.push_back(x2);
        }
    }

    if p1.len() > 0 {
        (0, p1)
    } else {
        // dbg!(p2);
        (1, p2)
    }
}

fn main() {
    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let mut decks = [VecDeque::new(), VecDeque::new()];

    let mut lines = lines.iter();

    for i in 0..2 {
        lines.next();

        while let Some(line) = lines.next() {
            if line == "" {
                break;
            }
            let x: usize = line.parse().unwrap();
            decks[i].push_back(x);
        }
    }

    let mut p1 = decks[0].clone();
    let mut p2 = decks[1].clone();

    let (_, p) = play(p1.make_contiguous(), p2.make_contiguous());

    let score: usize = p.iter().rev().enumerate().map(|(i, x)| (i as usize + 1) * x).sum();
    dbg!(score);
}