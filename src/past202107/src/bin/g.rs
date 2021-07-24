#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
    }

    let mut ans = vec![];
    let mut a = 1i64;
    let mut x = n as i64;
    
    while a < x {
        if x / a % 3 == 2 {
            ans.push(-a);
            x += a;
        }
        a *= 3;
    }
    a = 1;
    while x > 0 {
        match x % 3 {
            1 => ans.push(a),
            2 => panic!(),
            _ => {},
        }
        x /= 3;
        a *= 3;
    }
    let m = ans.len();
    println!("{}", m);
    for (i, x) in ans.iter().enumerate() {
        print!("{}{}", x, if i==m-1 {'\n'} else {' '});
    }

    dbg!(ans.iter().sum::<i64>());
}