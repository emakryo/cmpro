use std::io::Write;

macro_rules! eprintln {
    ($($args:tt)*) => { let _ = writeln!(&mut std::io::stderr(), $($args)*); }
}

fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}

struct Reader { v: Vec<String>, n: usize }

impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    fn next<T>(&mut self) -> T where T: std::str::FromStr, T::Err: std::fmt::Debug {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1;
        self.v[self.n-1].parse().expect(&self.v[self.n-1])
    }
    #[allow(dead_code)]
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        let mut v = Vec::with_capacity(n);
        for _ in 0..n { v.push(self.next()); }
        v
    }
}

use std::marker::PhantomData;
use std::ops::{Add, Sub, Mul, AddAssign, SubAssign, MulAssign};
// TODO: associated constants when compiler version is updated
pub trait Modulus { fn n() -> u64; }
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct MPrime;
impl Modulus for MPrime { fn n() -> u64 { 1000_000_007 } }
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Mod<M>(pub u64, PhantomData<M>);

impl<M: Modulus + Copy > Mod<M> {
    pub fn new(x: u64) -> Self { Mod(x % M::n(), PhantomData) }
    pub fn pow(self, n: u64) -> Self {
        match n {
            0 => Mod::new(1),
            n if n % 2 > 0 => self.pow(n-1) * self,
            n => { let x = self.pow(n/2); x * x },
        }
    }
    pub fn inv(self) -> Self { self.pow(M::n()-2) }
}
impl<M: Modulus + Copy> Default for Mod<M> { fn default() -> Self { Mod::new(0) } }
impl<M: Modulus + Copy> From<u64> for Mod<M> { fn from(x: u64) -> Mod<M> { Mod::new(x) } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> Add<T> for Mod<M> { type Output = Mod<M>;
    fn add(self, other: T) -> Mod<M> { Mod::new(self.0 + other.into().0) } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> Sub<T> for Mod<M> { type Output = Mod<M>;
    fn sub(self, other: T) -> Mod<M> { Mod::new((self.0 + M::n() - other.into().0)) } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> Mul<T> for Mod<M> { type Output = Mod<M>;
    fn mul(self, other: T) -> Mod<M> { Mod::new((self.0 * other.into().0)) } }
impl<M: Modulus + Copy> Add<Mod<M>> for u64 { type Output = Mod<M>;
    fn add(self, other: Mod<M>) -> Mod<M> { other.add(self) } }
impl<M: Modulus + Copy> Sub<Mod<M>> for u64 { type Output = Mod<M>;
    fn sub(self, other: Mod<M>) -> Mod<M> { other.sub(self) } }
impl<M: Modulus + Copy> Mul<Mod<M>> for u64 { type Output = Mod<M>;
    fn mul(self, other: Mod<M>) -> Mod<M> { other.mul(self) } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> AddAssign<T> for Mod<M> {
    fn add_assign(&mut self, other: T) { *self = self.add(other); } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> SubAssign<T> for Mod<M> {
    fn sub_assign(&mut self, other: T) { *self = self.sub(other); } }
impl<M: Modulus + Copy, T: Into<Mod<M>>> MulAssign<T> for Mod<M> {
    fn mul_assign(&mut self, other: T) { *self = self.mul(other); } }
pub type M = Mod<MPrime>;

fn main() {
    let mut r = Reader::new();
    let n = r.next();
    let a: Vec<u64> = r.nexts(n);

    let mut ones: Vec<u64> = vec![0; 61];
    for k in 0..61 {
        for i in 0..n {
            if ((a[i] >> k) & 1) > 0 {
                ones[k] += 1;
            }
        }
    }

    let mut ans: M = 0.into();
    for k in 0..61 {
        let o: M = (2 * ones[k] * (n as u64 - ones[k])).into();
        let m: u64 = 1 << k;
        ans += o * m;
    }
    println!("{}", (ans * M::new(2).inv()).0);
}
