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

#[cfg(test)]
mod tests {
    use super::*;
    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    struct M19;
    impl Modulus for M19 { fn n() -> u64 { 19 } }
    type M1 = Mod<M19>;
    #[test]
    fn test_new() {
        let _: M = Mod::new(7);
    }
    #[test]
    fn test_default() {
        let _: M = Default::default();
    }
    #[test]
    fn test_from() {
        let x: M = From::from(10);
        assert_eq!(x, Mod::new(10));
    }
    #[test]
    fn test_into() {
        let x: M = 10.into();
        assert_eq!(x, Mod::new(10));
    }
    #[test]
    fn test_add() {
        let x: M1 = Mod::new(7);
        let y: M1 = Mod::new(18);
        assert_eq!(x + y, Mod::new(6));
        assert_eq!(x, Mod::new(7));
    }
    #[test]
    fn test_add_u64() {
        let x: M1 = Mod::new(7);
        assert_eq!(x + 18, Mod::new(6));
        assert_eq!(18 + x, Mod::new(6));
        assert_eq!(x, Mod::new(7));
    }
    #[test]
    fn test_add_eq() {
        let mut x: M1 = Mod::new(7);
        let y = Mod::new(18);
        x += y;
        assert_eq!(x, Mod::new(6));
    }
    #[test]
    fn test_sub() {
        let x: M1 = Mod::new(7);
        let y = Mod::new(18);
        assert_eq!(x - y, Mod::new(8));
        assert_eq!(x, Mod::new(7));
    }
    #[test]
    fn test_sub_eq() {
        let mut x: M1 = Mod::new(7);
        let y = Mod::new(18);
        x -= y;
        assert_eq!(x, Mod::new(8));
    }
    #[test]
    fn test_mul() {
        let x: M1 = Mod::new(7);
        let y = Mod::new(18);
        assert_eq!(x * y, Mod::new(12));
    }
    #[test]
    fn test_mul_eq() {
        let mut x: M1 = Mod::new(7);
        let y = Mod::new(18);
        x *= y;
        assert_eq!(x, Mod::new(12));
    }
    #[test]
    fn test_pow() {
        let x: M1 = Mod::new(7);
        assert_eq!(x.pow(10), Mod::new(7));
    }
    #[test]
    fn test_inv() {
        let x: M1 = Mod::new(7);
        assert_eq!(x.inv(), Mod::new(11));
        assert_eq!(x.inv() * x, Mod::new(1));
    }
}
