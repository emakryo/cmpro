// cargo-deps: regex="1",anyhow="1"
use std::io::BufRead;

fn main() -> anyhow::Result<()> {
    let xs: Vec<u64> = std::io::stdin()
        .lock()
        .lines()
        .next().unwrap()?
        .split(',')
        .map(|x| x.parse().unwrap())
        .collect();
    
    let mut pos = std::collections::HashMap::<u64, (u64, Option<u64>)>::new();
    let mut last = 0;

    for i in 0..30000000 {
        if i < xs.len() {
            last = xs[i];
            if let Some(&(p0, p1)) = pos.get(&last) {
                pos.insert(last, (i as u64, Some(p0)));
            } else {
                pos.insert(last, (i as u64, None));
            }
        } else {
            if let Some(&(p0, p1)) = pos.get(&last){
                if let Some(p1) = p1 {
                    last = p0 - p1;
                } else {
                    last = 0;
                }
                if let Some(&(q0, _)) = pos.get(&last) {
                    pos.insert(last, (i as u64, Some(q0)));
                } else {
                    pos.insert(last, (i as u64, None));
                }
            } else {
                last = 0;
                if let Some(&(q0, _)) = pos.get(&last) {
                    pos.insert(last, (i as u64, Some(q0)));
                } else {
                    pos.insert(last, (i as u64, None));
                }
            }
        }
    }

    dbg!(last);

    Ok(())
}