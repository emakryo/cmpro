pub mod modulo;
pub mod lca;
pub mod union_find;
pub mod segment_tree;
pub mod combination;

#[cfg(test)]
mod modulo_tests {
    use super::modulo::*;
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
    #[test]
    fn test_fact() {
        let c: Combination<MPrime> = Combination::new(1000000);
        for i in 1..1000 {
            let x = c.fact(i * 103);
            let y = c.fact(i * 103 + 1);
            if (i * 103 + 1) % MPrime::n() != 0 {
                assert_eq!(x.0 * (i * 103 + 1), y.0);
                assert_eq!(x.1, y.1);
            }
        }
    }
    #[test]
    fn test_comb() {
        let c: Combination<MPrime> = Combination::new(1000000);

        for x in 2..100 {
            for y in 2..100{
                let x = x * 109;
                let y = y * 103;
                if x < y { continue; }
                assert_eq!(c.comb(x, y), c.comb(x, x-y));
                assert_eq!(c.comb(x, y), (c.comb(x-1, y-1) + c.comb(x-1, y)));
            }
        }
    }
}
