// cargo-deps: regex="1"

use std::collections::HashMap;
use std::io::BufRead;

#[derive(Clone, Copy, Debug)]
enum Dir {
    TopA,
    LeftA,
    RightA,
    ButtomA,
    TopB,
    LeftB,
    RightB,
    ButtomB,
}

const DIRS: [Dir; 8] = [
    Dir::TopA,
    Dir::LeftA,
    Dir::RightA,
    Dir::ButtomA,
    Dir::TopB,
    Dir::LeftB,
    Dir::RightB,
    Dir::ButtomB,
];

#[derive(Clone, Debug, Default)]
struct Tile(Vec<Vec<char>>);

impl std::fmt::Display for Tile {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for xs in &self.0 {
            let s: String = xs.iter().collect();
            writeln!(f, "{}", s)?;
        }
        Ok(())
    }
}

impl Tile {
    fn new(x: Vec<String>) -> Self {
        Tile(x.into_iter().map(|s| s.chars().collect()).collect())
    }

    fn empty() -> Self {
        Tile(vec![])
    }

    fn width(&self) -> usize {
        (self.0).get(0).map(|x| x.len()).unwrap_or(0)
    }

    fn height(&self) -> usize {
        self.0.len()
    }

    fn rot90(&self) -> Self {
        Self::new((0..self.width()).rev().map(|i| {
            self.0.iter().map(|s| s[i]).collect()
        }).collect())
    }

    fn rot180(&self) -> Self {
        self.rot90().rot90()
    }

    fn rot270(&self) -> Self {
        self.rot180().rot90()
    }

    /// flip horizontally
    fn flip(&self) -> Self {
        Self::new(self.0.iter().cloned().map(|s| s.iter().rev().cloned().collect()).collect())
    }

    fn edge(&self, dir: Dir) -> u32 {
        use Dir::*;
        let h = self.height();
        let w = self.width();
        match dir {
            TopA => encode((self.0)[0].iter().cloned()),
            RightA => encode(self.0.iter().map(|x| x[w-1])),
            ButtomA => encode((self.0)[h-1].iter().rev().cloned()),
            LeftA => encode(self.0.iter().rev().map(|x| x[0])),
            TopB => encode((self.0)[0].iter().rev().cloned()),
            RightB => encode(self.0.iter().map(|x| x[w-1]).rev()),
            ButtomB => encode((self.0)[h-1].iter().cloned()),
            LeftB => encode(self.0.iter().map(|x| x[0])),
        }
    }

    fn hconcat(&self, other: &Self) -> Self {
        let w1 = self.width();
        let w2 = other.width();
        if w1 == 0 {
            return other.clone();
        }

        Self::new(
            self
                .0
                .iter()
                .zip(other.0.iter())
                .map(|(a, b)| {
                    a[0..w1-1].iter().chain(b[1..w2].iter()).cloned().collect()
                }).collect()
        )
    }

    fn vconcat(&self, other: &Self) -> Self {
        let h1 = self.height();
        let h2 = other.height();
        if h1 == 0 {
            return other.clone();
        }
        Self(
            self
                .0
                .iter()
                .take(h1-1)
                .cloned()
                .chain(other.0.iter().skip(1).cloned())
                .collect()
        )
    }

    fn trim(&mut self) {
        let h = self.height();
        self.0.remove(0);
        self.0.remove(h-2);

        let w = self.width();
        self.0.iter_mut().for_each(|s| {
            s.remove(0);
            s.remove(w-2);
        });
    }

    fn mark(&mut self, xs: &[Vec<char>]) {
        let h = self.height();
        let w = self.width();
        let mh = xs.len();
        let mw = xs[0].len();

        for i in 0..(h-mh+1) {
            for j in 0..(w-mw+1) {
                let mut ok = true;
                for x in 0..mh {
                    for y in 0..mw {
                        if xs[x][y] == '#' && self.0[i+x][j+y] == '.' {
                            ok = false
                        }
                    }
                }
                if !ok {
                    continue;
                }

                for x in 0..mh {
                    for y in 0..mw {
                        if xs[x][y] == '#' {
                            self.0[i+x][j+y] = 'O';
                        }
                    }
                }
            }
        }

    }

    fn count(&self, x: char) -> usize {
        self.0.iter().map(|s| {
            s.iter().filter(|&&c| c == x).count()
        }).sum()
    }
}

fn encode(x: impl Iterator<Item=char>) -> u32 {
    x.fold(0, |mut a, b| {
        a *= 2;
        if b == '#' {
            a += 1;
        }
        a
    })
}

fn main() {
    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let mut tiles = HashMap::new();
    let mut n: usize = 0;
    let mut xs = vec![];
    let re = regex::Regex::new(r"^Tile (\d+):$").unwrap();
    for (i, line) in lines.into_iter().enumerate() {
        if i % 12 == 0 {
            n = re.captures(&line).unwrap()[1].parse().unwrap();
        } else if i % 12 < 11 {
            xs.push(line);
        } else {
            tiles.insert(n, Tile::new(xs));
            xs = vec![];
        }
    }

    let mut edges: HashMap<u32, Vec<(_, _)>> = HashMap::new();
    for (&id, tile) in &tiles {
        for dir in DIRS.iter() {
            let t = tile.edge(*dir);
            if let Some(x) = edges.get_mut(&t) {
                x.push((id, dir));
            } else {
                edges.insert(t, vec![(id, dir)]);
            }
        }
    }

    let mut index = vec![vec![0; 12]; 12];
    let mut array = vec![vec![Tile::default(); 12]; 12];

    for (id, tile) in &tiles {
        let t = tile.edge(Dir::TopA);
        let r = tile.edge(Dir::RightA);
        let b = tile.edge(Dir::ButtomA);
        let l = tile.edge(Dir::LeftA);

        let ads = [
            edges.get(&t).unwrap().len(),
            edges.get(&r).unwrap().len(),
            edges.get(&b).unwrap().len(),
            edges.get(&l).unwrap().len(),
        ];

        if ads == [1, 2, 2, 1] {
            index[0][0] = *id;
            array[0][0] = tiles.get(id).unwrap().clone();
            break;
        } else if ads == [1, 1, 2, 2] {
            index[0][0] = *id;
            array[0][0] = tiles.get(id).unwrap().rot90();
            break;
        } else if ads == [2, 1, 1, 2] {
            index[0][0] = *id;
            array[0][0] = tiles.get(id).unwrap().rot180();
            break;
        } else if ads == [2, 2, 1, 1] {
            index[0][0] = *id;
            array[0][0] = tiles.get(id).unwrap().rot270();
            break;
        }

    }

    tiles.remove(&index[0][0]);

    for i in 0..12 {
        for j in 0..12 {
            if i == 0 && j == 0 {
                continue;
            } else if i == 0 {
                let adj = index[i][j-1];
                let edge = array[i][j-1].edge(Dir::RightB);
                let (id, dir) = edges
                    .get(&edge)
                    .unwrap()
                    .iter()
                    .filter(|x| x.0 != adj)
                    .next()
                    .unwrap();

                let tile = tiles.remove(id).unwrap();
                let tile = match dir {
                    Dir::TopA => tile.rot90(),
                    Dir::RightA => tile.rot180(),
                    Dir::ButtomA => tile.rot270(),
                    Dir::LeftA => tile,
                    Dir::TopB => tile.flip().rot90(),
                    Dir::RightB => tile.flip(),
                    Dir::ButtomB => tile.flip().rot270(),
                    Dir::LeftB => tile.rot90().flip().rot270(),
                };

                // dbg!(i, j, id);
                // println!("{}", &tile);
                index[i][j] = *id;
                array[i][j] = tile;

            } else {
                let adj = index[i-1][j];
                let edge = array[i-1][j].edge(Dir::ButtomB);

                let (id, dir) = edges
                    .get(&edge)
                    .unwrap()
                    .iter()
                    .filter(|x| x.0 != adj)
                    .next()
                    .unwrap();

                // dbg!(i, j, id, dir);

                let tile = tiles.remove(id).unwrap();
                let tile = match dir {
                    Dir::TopA => tile,
                    Dir::RightA => tile.rot90(),
                    Dir::ButtomA => tile.rot180(),
                    Dir::LeftA => tile.rot270(),
                    Dir::TopB => tile.flip(),
                    Dir::RightB => tile.rot90().flip(),
                    Dir::ButtomB => tile.rot180().flip(),
                    Dir::LeftB => tile.rot270().flip(),
                };
                // println!("{}", &tile);

                index[i][j] = *id;
                array[i][j] = tile;
            }
        }
    }

    assert_eq!(tiles.len(), 0);

    let mut img = array.into_iter().map(|xs| {
        xs.into_iter().fold(Tile::empty(), |a, b| {
            a.hconcat(&b)
        })
    }).fold(Tile::empty(), |a, b| {
        a.vconcat(&b)
    });

    img.trim();

    dbg!(img.height(), img.width());
    dbg!(img.count('#'));

    let mark: Vec<Vec<char>> = [
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   ",
    ].into_iter().map(|s| s.chars().collect()).collect();


    img.mark(&mark);
    for _ in 0..3 {
        img = img.rot90();
        img.mark(&mark);
    }

    img = img.flip();
    img.mark(&mark);
    for _ in 0..3 {
        img = img.rot90();
        img.mark(&mark);
    }

    dbg!(img.count('#'));
}