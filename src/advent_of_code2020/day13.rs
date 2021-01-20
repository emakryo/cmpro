use std::io::BufRead;

fn ext_gcd(a: u64, b: u64) -> (i64, i64, i64) {
    match b {
        0 => (1, 0, a as i64),
        b => {
            let (x, y, g) = ext_gcd(b, a%b);
            (y, x-((a/b) as i64)*y, g)
        }
    }
}

fn crt(r: &[u64], m: &[u64]) -> i64 {
    let p: u64 = m.iter().product();
    let b: Vec<i64> = m.iter().map(|&m| {
        let n = p/m;
        let (a, _, g) = ext_gcd(n, m);
        assert_eq!(g, 1);
        dbg!(a, n, a as u64*n%m);
        a * n as i64
    }).collect();

    let mut x = b.iter().zip(r.iter()).map(|(b, r)| b*(*r as i64)).sum::<i64>();
    while(x < 0){
        x += p as i64;
    }
    x % p as i64
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>()?;

    let _begin: u64 = lines[0].parse()?;
    let (ns, xs) = lines[1].split(',')
        .enumerate()
        .filter_map(|(i, x)| x.parse::<u64>().map(|x| (i, x)).ok())
        .fold((vec![], vec![]), |(mut xs, mut ys), (x, y)| {
            xs.push(((-(x as i64) % y as i64) + y as i64) as u64);
            ys.push(y);
            (xs, ys)
        });


    let z = crt(&ns, &xs);
    dbg!(z);
    Ok(())
}