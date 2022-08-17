pub fn kmp<T: PartialEq>(a: &[T]) -> Vec<i64> {
    let mut x = vec![-1; a.len()+1];
    let mut j = -1;
    for i in 0..a.len() {
        while j >= 0 && a[i] != a[j as usize] {
            j = x[j as usize];
        }
        j += 1;
        if i+1 < a.len() && a[i+1] == a[j as usize] {
            x[i+1] = x[j as usize];
        } else {
            x[i+1] = j;
        }
    }

    x
}
