// cargo-deps: regex="1",anyhow="1"
use std::io::BufRead;

fn set_bit(x: u64, pos: usize, bit: u64) -> u64 {
    match bit {
        0 => x & (!(1<<pos)),
        1 => x | (1<<pos),
        _ => panic!(),
    }
}

fn main() -> anyhow::Result<()> {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>()?;

    let mut s = std::collections::HashMap::<u64, u64>::new();
    let mut mask: Vec<_> = lines[0].split(' ').nth(2).unwrap().chars().collect();
    let re_mem = regex::Regex::new(r"mem\[(\d+)\] = (\d+)")?;
    for line in &lines[1..] {
        if let Some(cap) = re_mem.captures(line) {
            let addr: u64 = cap[1].parse()?;
            let val: u64 = cap[2].parse()?;

            let nx = mask.iter().filter(|c| **c == 'X').count();
            dbg!(&mask, nx);
            for b in 0..(1 << nx) {
                let mut addr = addr;
                let mut j = 0;
                for k in 0..36 {
                    if mask[k] == 'X' {
                        addr = set_bit(addr, 35-k, b>>j&1);
                        j += 1;
                    } else if mask[k] == '1' {
                        addr = set_bit(addr, 35-k, 1);
                    }
                }
                //dbg!(addr, val);
                s.insert(addr, val);
            }
        } else {
            mask = line.split(' ').nth(2).unwrap().chars().collect()
        }
    }

    let ans: u64 = s.iter().map(|(_, v)| v).sum();
    dbg!(ans);
    Ok(())
}
