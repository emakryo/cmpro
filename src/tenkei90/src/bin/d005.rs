mod modulo {
    use std::fmt::Display;
    use std::fmt::Formatter;
    use std::marker::PhantomData;
    use std::ops::Div;
    use std::ops::DivAssign;
    use std::ops::{Add, Sub, Mul, AddAssign, SubAssign, MulAssign};
    // TODO: Use const generics when compiler version is updated

    pub trait Modulus { const M: u64; }

    #[derive(Debug, Default, Clone, Copy)]
    pub struct Modulus0;
    impl Modulus for Modulus0 { const M: u64 = 1_000_000_007; }

    #[derive(Debug, Default, Clone, Copy)]
    pub struct ModInt<M>(u64, PhantomData<M>);

    impl<M: Modulus + Copy> ModInt<M> {
        pub fn new(x: u64) -> Self { ModInt(x % M::M, PhantomData) }
        pub fn pow(self, n: u64) -> Self {
            match n {
                0 => ModInt::new(1),
                n if n % 2 > 0 => self.pow(n-1) * self,
                n => { let x = self.pow(n/2); x * x },
            }
        }
        pub fn neg(self) -> Self { Self::new(M::M - self.0) }
        pub fn inv(self) -> Self { self.pow(M::M-2) }
    }

    impl<M> Display for ModInt<M> {
        fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
            self.0.fmt(f)
        }
    }

    macro_rules! impl_from {
        ($t:ty) => {
            impl<M: Modulus + Copy> From<$t> for ModInt<M> { fn from(x: $t) -> ModInt<M> {
                let m = M::M as $t;
                ModInt::new((x % m + m) as u64)
            } }
        };
    }
    impl_from!(u32);
    impl_from!(u64);
    impl_from!(usize);
    impl_from!(i32);
    impl_from!(i64);
    impl_from!(isize);

    macro_rules! impl_op {
        ($trait:tt, $method:ident, $func:expr) => {
            impl<M: Modulus + Copy, T: Into<ModInt<M>>> $trait<T> for ModInt<M> {
                type Output = ModInt<M>;
                fn $method(self, other: T) -> ModInt<M> { ModInt::new(($func)(self, other.into())) }
            }
        };
    }

    impl_op!(Add, add, |x: ModInt<M>, y: ModInt<M>| x.0 + y.0);
    impl_op!(Mul, mul, |x: ModInt<M>, y: ModInt<M>| x.0 * y.0);
    impl_op!(Sub, sub, |x: ModInt<M>, y: ModInt<M>| M::M + x.0 - y.0);
    impl_op!(Div, div, |x: ModInt<M>, y: ModInt<M>| x.0 * y.inv().0);

    macro_rules! impl_ops_type {
        ($t:ty) => {
            macro_rules! impl_rop {
                ($trait:tt, $method:ident, $func:expr) => {
                    impl<M: Modulus + Copy> $trait<ModInt<M>> for $t {
                        type Output = ModInt<M>;
                        fn $method(self, other: ModInt<M>) -> ModInt<M> { ($func)(self, other) }
                    }
                };
            }

            impl_rop!(Add, add, |x: $t, y: ModInt<M>| y + x);
            impl_rop!(Sub, sub, |x: $t, y: ModInt<M>| ModInt::<M>::from(x) + y.neg());
            impl_rop!(Mul, mul, |x: $t, y: ModInt<M>| y * x);
            impl_rop!(Div, div, |x: $t, y: ModInt<M>| ModInt::<M>::from(x) * y.inv());
        };
    }
    impl_ops_type!(u32);
    impl_ops_type!(u64);
    impl_ops_type!(usize);
    impl_ops_type!(i32);
    impl_ops_type!(i64);
    impl_ops_type!(isize);

    macro_rules! impl_op_assign {
        ($trait:tt, $assign_method:ident, $method:ident) => {
            impl<M: Modulus + Copy, T: Into<ModInt<M>>> $trait<T> for ModInt<M> {
                fn $assign_method(&mut self, other: T) { *self = self.$method(other); }
            }
        };
    }
    impl_op_assign!(AddAssign, add_assign, add);
    impl_op_assign!(SubAssign, sub_assign, sub);
    impl_op_assign!(MulAssign, mul_assign, mul);
    impl_op_assign!(DivAssign, div_assign, div);

    /*
    pub struct Combination<M>(Vec<ModInt<M>>);
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
    */
    pub type Mint = ModInt<Modulus0>;

    #[cfg(test)]
    mod tests {
        use super::*;
        #[derive(Debug, Default, Clone, Copy)]
        struct Modulus7;
        impl Modulus for Modulus7 { const M: u64 = 7; }
        type Mint = ModInt<Modulus7>;
    
        #[test]
        fn test_ops() {
            let x = Mint::new(10);
            assert_eq!(x.0, 3);
            assert_eq!((x + 3).0, 6);
            assert_eq!((x - 4).0, 6);
            assert_eq!((x * 4).0, 5);
            assert_eq!((x / 4).0, 6);
            assert_eq!((3u64 + x).0, 6);
            assert_eq!((4u32 - x).0, 1);
            assert_eq!((4i32 * x).0, 5);
            assert_eq!((4i64 / x).0, 6);

            let mut x = Mint::new(10);
            x += 3;
            assert_eq!(x.0, 6);
            x *= 2;
            assert_eq!(x.0, 5);
            x /= 4;
            assert_eq!(x.0, 3);
        }
    }
}

fn main() {
    proconio::input! {
        n: usize,
        b: usize,
        k: usize,
        c: [usize; k],
    }

}