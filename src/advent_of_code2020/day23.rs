
fn next(xs: Vec<u8>) -> Vec<u8> {
    let mut dest = xs[0];

    while dest == xs[0] || dest == xs[1] || dest == xs[2] || dest == xs[3] {
        dest = (dest + 7) % 9 + 1;
    }

    let dest_idx = xs.iter().enumerate().filter(|(_, &x)| x == dest).next().unwrap().0;

    let mut ys = vec![];
    ys.extend(&xs[4..(dest_idx+1)]);
    ys.extend(&xs[1..4]);
    if dest_idx < 9 {
        ys.extend(&xs[(dest_idx+1)..]);
    }
    ys.extend(&xs[0..1]);

    ys
}

fn main() {
    use std::io::BufRead;

    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let n = 1000000;
    // let n = 9;
    let xs: Vec<usize> = lines[0]
        .chars()
        .map(|x| String::from(x).parse::<usize>().unwrap()-1)
        .chain(9..n)
        .collect();

    let mut left: Vec<usize> = vec![0; n];
    let mut right: Vec<usize> = vec![0; n];

    for i in 0..n {
        let j = (i+1)%n;
        right[xs[i]] = xs[j];
        left[xs[j]] = xs[i];
    }

    // dbg!(&xs);
    // dbg!(&left);
    // dbg!(&right);

    let mut x = xs[0];
    for _ in 0..10000000 {
        let mut dest = if x > 0 {
            x-1
        } else {
            n-1
        };
        // dbg!(x, dest);
        let nexts = [right[x], right[right[x]], right[right[right[x]]]];
        while nexts.iter().any(|&a| a == dest) {
            if dest > 0 {
                dest -= 1;
            } else {
                dest = n-1;
            }
        }

        let nx = right[nexts[2]];
        let dest_right = right[dest];
        right[x] = nx;
        left[nx] = x;
        right[dest] = nexts[0];
        left[nexts[0]] = dest;
        right[nexts[2]] = dest_right;
        left[dest_right] = nexts[2];

        x = nx;
    }

    let rx = right[0]+1;
    let rrx = right[rx-1]+1;
    dbg!(rx, rrx, rx*rrx);
}
