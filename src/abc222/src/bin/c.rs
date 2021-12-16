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
        a: [Chars; 2*n],
    }

    let mut rank = (0..2*n).collect::<Vec<_>>();
    let mut score = vec![0; 2*n];

    for i in 0..m {
        for j in 0..n {
            let x = a[rank[2*j]][i];
            let y = a[rank[2*j+1]][i];

            match (x, y) {
                ('G', 'C') | ('C', 'P') | ('P', 'G') => {
                    score[rank[2*j]] += 1;
                },
                ('C', 'G') | ('P', 'C') | ('G', 'P') => {
                    score[rank[2*j+1]] += 1;
                },
                _ => (),
            }
        }

        rank.sort_by_key(|&i| (-score[i], i));
        dbg!(&rank);
        dbg!(&score);
    }


    for x in rank {
        println!("{}", x+1);
    }
}