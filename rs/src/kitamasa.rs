pub fn kitamasa<T>(a: &[T], c: &[T], n: usize) -> T 
where T: Clone + Copy + std::ops::Mul<Output=T> + std::ops::Add<Output=T> + From<usize>
{
    let k = a.len();
    assert_eq!(k, c.len());

    fn rec<T>(c: &[T], n: usize) -> Vec<T>
    where T: Clone + Copy + std::ops::Mul<Output=T> + std::ops::Add<Output=T> + From<usize>
    {
        let k = c.len();
        let r = if n < k  {
            let mut b = vec![T::from(0); k];
            b[k-n-1] = 1.into();
            b
        } else if n % 2 == 1 {
            let b = rec(c, n-1);
            let mut bb = c.to_owned();
            for i in 0..k {
                bb[i] = bb[i] * b[0];
            }
            for i in 0..k-1 {
                bb[i] = bb[i] + b[i+1];
            }
            bb
        } else {
            let b = rec(c, n/2);

            let mut bb = vec![T::from(0); 2*b.len()-1];
            for i in 0..k {
                for j in 0..k {
                    bb[i+j] = bb[i+j] + b[i]*b[j];
                }
            }

            for s in 0..k-1 {
                for i in 0..k {
                    bb[s+i+1] = bb[s+i+1] + bb[s] * c[i];
                }
            }
            bb[k-1..].to_owned()
        };
        r
    }

    let b = rec(c, n);

    let mut x = T::from(0);
    for (&ai, &bi) in a.iter().zip(b.iter()) {
        x = x + ai * bi;
    }

    x
}
