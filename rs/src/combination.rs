/// Extended Euclid's greatest common divisor algorithm
/// Find (x, y, g)
/// where $a*x + b*y = g$ and g is the greatest common divisor of (a, b)
pub fn ext_gcd(a: i64, b: i64) -> (i64, i64, i64) {
    if b == 0 { (1, 0, a)
    } else {
        let (nx, ny, g) = ext_gcd(b, a % b); (ny, nx - a / b * ny, g)
    }
}

/// Modular inverse of x given modulo p, y
/// x*y = 1 mod p
/// <=> x*y + z*p = 1
pub fn inv_mod(x: u64, n: u64) -> u64 {
    let x = x as i64;
    let n = n as i64;
    let (y, _, _) = ext_gcd(x, n); (if y > 0 { y % n } else { n + y % n }) as u64
}

/// Modular factorial of n, also counting p's appearance e
/// n! = a * p^e
/// return: (a, e)
/// n! = n * (n-1) * ... * (k*p+1) *
///      (k*p) * (k*p-1) * ... ((k-1)*p+1) *
///      ...
///      p * (p-1) * ... * 2 * 1   (k = floor(n/p))
///    = (n%p) * ... * 1 *
///      (k*p) * (p-1) * ... * 1 *
///      p * (p-1) * ... * 1       (mod p, preserving p's multiples)
///    = (n%p)! * p^k * k! * (p-1)^k
///    = (n%p)! * p^k * k! * (p-1)^(k%2)
///
/// From the facts:
///   (p-1)! = p-1 (mod p) (c.f. Willson's theorem)
///   (p-2)**2 = 1 (mod p)
pub fn fact_mod(n: u64, p: u64, fact: &[u64]) -> (u64, u64) {
    if n < p { return (fact[n as usize], 0); }
    let k = n / p;
    let (a, e) = fact_mod(k, p, fact);
    (fact[(n % p) as usize] * a * ((p - 2) * k % 2 + 1) % p, e + k)
}

/// Modular combination (n, m) given module p
/// (n, m) = n!/(n-m)!m!
///        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
///        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
pub fn comb_mod(n: u64, m: u64, p: u64, fact: &[u64]) -> u64{
    if n < m { panic!("{} < {}", n, m); }
    let (an, en) = fact_mod(n, p, fact);
    let (am, em) = fact_mod(m, p, fact);
    let (al, el) = fact_mod(n-m, p, fact);
    if en > em + el { 0 } else { an * inv_mod(am * al % p, p) % p }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_ext_gcd() {
        let a = 10;
        let b = 8;
        let (x, y, d) = ext_gcd(a, b);

        assert_eq!(d, 2);
        assert_eq!(a * x + b * y, d);
    }

    #[test] 
    fn test_inv_mod() {
        for i in 1..10007 {
            let p = 10007;
            let d = inv_mod(i, p);
            assert_eq!(i * d % p, 1);
        }
    }

    #[test]
    fn test_fact_mod() {
        let p = 10007;
        let fact: Vec<u64> = (0..1000000).scan(1, |s, x| {
            *s = if x == 0 { 1 } else { *s * x % p }; Some(*s)
        }).collect();

        assert_eq!(fact[0], 1);
        assert_eq!(fact[1], 1);
        assert_eq!(fact[2], 2);
        assert_eq!(fact[3], 6);
        assert_eq!(fact[100] * 101 % p, fact[101]);

        for i in 1..10000 {
            println!("{}", i);
            let x = fact_mod(i * 1003, p, &fact);
            let y = fact_mod(i * 1003 + 1, p, &fact);
            if (i * 1003 + 1) % p != 0 {
                assert_eq!(x.0 * (i * 1003 + 1) % p, y.0);
                assert_eq!(x.1, y.1);
            }
        }
    }

    #[test]
    fn test_comb_mod() {
        let p = 10007;
        let fact: Vec<u64> = (0..1000000).scan(1, |s, x| {
            *s = if x == 0 { 1 } else { *s * x % p }; Some(*s)
        }).collect();

        for x in 2..100 {
            for y in 2..100{
                let x = x * 109;
                let y = y * 103;
                if x < y { continue; }
                assert_eq!(comb_mod(x, y, p, &fact), comb_mod(x, x-y, p, &fact));
                assert_eq!(
                    comb_mod(x, y, p, &fact),
                    (comb_mod(x-1, y-1, p, &fact) + comb_mod(x-1, y, p, &fact)) % p
                );
            }
        }
    }
}
