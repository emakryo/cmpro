fn main() {
    use std::io::BufRead;

    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let k1: u64 = lines[0].parse().unwrap();
    let k2: u64 = lines[1].parse().unwrap();

    let m = 20201227;
    let mut loop_size = vec![0; m];
    let mut x = 1;
    for i in 0..m {
        loop_size[x as usize] = i;
        x = x * 7 % m;
    }

    let l1 = loop_size[k1 as usize];
    let l2 = loop_size[k2 as usize];

    let mut e = 1;
    for _ in 0..l1 {
        e = (e * k2) % m as u64;
    }

    dbg!(k1, k2, l1, l2);
    dbg!(e);
}