use std::collections::{HashMap, HashSet};
enum Dir {
    E,
    Se,
    Sw,
    W,
    Nw,
    Ne,
}

fn main() {
    use std::io::BufRead;

    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let mut pos = HashMap::new();

    for line in lines {
        let line: Vec<u8> = line.into();
        let mut ds = vec![];
        let mut i = 0;
        while i < line.len()-1 {
            match (line[i] as char, line[i+1] as char) {
                ('e', _) => {
                    i += 1;
                    ds.push(Dir::E);
                }
                ('w', _) => {
                    i += 1;
                    ds.push(Dir::W);
                }
                ('s', 'e') => {
                    i += 2;
                    ds.push(Dir::Se);
                }
                ('s', 'w') => {
                    i += 2;
                    ds.push(Dir::Sw);
                }
                ('n', 'e') => {
                    i += 2;
                    ds.push(Dir::Ne);
                }
                ('n', 'w') => {
                    i += 2;
                    ds.push(Dir::Nw);
                }
                _ => panic!(),
            }
        }

        if i < line.len() {
            match line[i] as char {
                'e' => ds.push(Dir::E),
                'w' => ds.push(Dir::W),
                _ => panic!(),
            }
        }

        let mut p = (0, 0);
        for dir in ds {
            p = match (dir, p) {
                (Dir::E, (x, y)) => (x+1, y),
                (Dir::W, (x, y)) => (x-1, y),
                (Dir::Se, (x, y)) if y % 2 == 0 => (x, y-1),
                (Dir::Se, (x, y)) => (x+1, y-1),
                (Dir::Sw, (x, y)) if y % 2 == 0 => (x-1, y-1),
                (Dir::Sw, (x, y)) => (x, y-1),
                (Dir::Ne, (x, y)) if y % 2 == 0 => (x, y+1),
                (Dir::Ne, (x, y)) => (x+1, y+1),
                (Dir::Nw, (x, y)) if y % 2 == 0 => (x-1, y+1),
                (Dir::Nw, (x, y)) => (x, y+1),
            }
        }

        if !pos.contains_key(&p) {
            pos.insert(p, 0);
        }

        let x = pos.get_mut(&p).unwrap();
        *x = *x+1;
    }

    let mut black: HashSet<(i64, i64)> = pos.into_iter().filter_map(|(p, x)| {
        if x%2==1 {
            Some(p)
        } else {
            None
        }
    }).collect();
    dbg!(&black);

    let dxs = [
        [0, -1, 1, -1, 0, -1],
        [1, 0, 1, -1, 1, 0],
    ];
    let dys = [
        [1, 1, 0, 0, -1, -1],
        [1, 1, 0, 0, -1, -1],
    ];

    for i in 0..100 {
        let mut n_adj = HashMap::new();

        for &(x, y) in &black {
            let my = y.rem_euclid(2) as usize;
            for (&dx, &dy) in dxs[my].iter().zip(dys[my].iter()) {
                let dx = x + dx;
                let dy = y + dy;

                if !n_adj.contains_key(&(dx, dy)) {
                    n_adj.insert((dx, dy), 0);
                }

                let x = n_adj.get_mut(&(dx, dy)).unwrap();
                *x = *x+1;
            }
        }

        let mut next = HashSet::new();

        for ((x, y), n) in n_adj {
            if black.contains(&(x, y)) {
                if n == 1 || n == 2{
                    next.insert((x, y));
                }
            } else {
                if n == 2 {
                    next.insert((x, y));
                }
            }
        }

        black = next;

        dbg!(i, black.len());
    }
}


//1:  -3 -2 -1 0 1 2 3 4
//0: -3 -2 -1 0 1 2 3 4
//-1: -3 -2 -1 0 1 2 3 4
//           

