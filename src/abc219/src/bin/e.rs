#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}


fn main() {
    proconio::input!{
        a: [[usize; 4]; 4],
    }

    let mut s = 0;
    for i in 0..4 {
        for j in 0..4 {
            s += a[i][j]<<(4*i+j);
        }
    }

    let mut ans = 0;
    let f = |i: usize| {
        if s & (((1<<16)-1)^i) > 0 {
            return 0;
        }
        let c = i.count_ones();
        let mut d = 0;
        for j in 0..16 {
            if i>>j&1 == 0 { continue; }
            let mut visit = 0;
            d = dfs(j, i, &mut visit);
            break;
        }
        if c != d {
            return 0;
        }

        let mut ok = 0;
        for j in 0..16 {
            if i>>j&1 == 1 { continue; }
            let mut visit = 0;
            check(j, i, &mut ok, &mut visit);
        }
        // eprintln!("0x{:X}", ok);

        if i|ok != (1<<16)-1 {
            return 0;
        }

        return 1;


        fn dfs(u: usize, s: usize, visit: &mut usize) -> u32 {
            let mut ret = 1;
            *visit += 1 << u;
            let x = u / 4;
            let y = u % 4;
            let dx = [1, 0, 3, 0];
            let dy = [0, 1, 0, 3];
            for k in 0..4 {
                let nx = (x + dx[k]) % 4;
                let ny = (y + dy[k]) % 4;
                if (x==0&&nx==3) || (x==3&&nx==0) || (y==0&&ny==3) || (y==3&&ny==0) {
                    continue;
                }
                let v = nx*4 + ny;
                if s>>v&1 == 0 || *visit>>v&1 > 0 {
                    continue;
                }
                ret += dfs(v, s, visit);
            }

            ret
        }

        fn check(u: usize, s: usize, ok: &mut usize, visit: &mut usize) -> bool {
            *visit += 1 << u;
            if *ok >> u & 1 == 1 {
                return true;
            }
            let x = u / 4;
            let y = u % 4;

            if x == 0 || x == 3 || y == 0 || y == 3 {
                *ok += 1 << u;
                return true;
            }
            let dx = [1, 0, 3, 0];
            let dy = [0, 1, 0, 3];
            for k in 0..4 {
                let nx = (x + dx[k]) % 4;
                let ny = (y + dy[k]) % 4;
                if (x==0&&nx==3) || (x==3&&nx==0) || (y==0&&ny==3) || (y==3&&ny==0) {
                    continue;
                }
                let v = nx*4 + ny;
                if s>>v&1 == 1 || *visit>>v&1 > 0 {
                    continue;
                }
                if check(v, s, ok, visit) {
                    *ok += 1 << u;
                    return true;
                }
            }
            return false;
        }
    };

    for i in 1..(1<<16) {
        ans += f(i);
    }
    eprintln!("0x{:X}", s);
    dbg!(f(0xf8cf));

    println!("{}", ans);
}