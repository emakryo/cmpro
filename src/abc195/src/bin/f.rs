fn main() {
    proconio::input!{
        (a, b): (u64, u64),
    }

    let mut sieve = vec![false; 73];

    for i in 2..73 {
        if sieve[i] { continue }
        let mut j = 2*i;
        while j < 73 {
            sieve[j] = true;
            j += i;
        }
    }

    let primes = sieve.iter().enumerate().filter_map(|(i, x)| {
        if !*x && i>=2 {
            Some(i as u64)
        } else {
            None
        }
    }).collect::<Vec<_>>();

    let mut dp = vec![0u64; 1<<primes.len()];
    dp[0] = 1;
    for x in a..=b {
        let mut z = 0;
        for (i, &p) in primes.iter().enumerate() {
            if x % p== 0 {
                z += 1<<i;
            }
        }

        let mut next = dp.clone();
        for i in 0..(1<<primes.len()) {
            if z & i > 0 { continue }
            next[z|i] += dp[i];
        }
        dp = next;
    }

    println!("{}", dp.iter().sum::<u64>());
}