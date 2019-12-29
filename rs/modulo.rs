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

pub struct Combination<M>(Vec<Mod<M>>);
impl<M: Modulus + Copy> Combination<M> {
    pub fn new(n: u64) -> Self {
        let fact: Vec<Mod<M>> = (0..n).scan(1.into(), |s, x| {
            *s = if x == 0 { 1.into() } else { *s * x }; Some(*s)
        }).collect(); Combination(fact)
    }
    pub fn fact(&self, n: u64) -> (Mod<M>, u64) {
        let p = M::n();
        if n < p { return ((self.0)[n as usize], 0); }
        let k = n / p; let (a, e) = self.fact(k.into());
        ((self.0)[(n % p) as usize] * a * ((p - 2) * k % 2 + 1), e + k)
    }
    pub fn comb(&self, n: u64, m: u64) -> Mod<M> {
        if n < m { panic!("{} < {}", n, m); }
        let (an, en) = self.fact(n); let (am, em) = self.fact(m); let (al, el) = self.fact(n-m);
        if en > em + el { 0.into() } else { an * (am * al).inv() }
    }
}
