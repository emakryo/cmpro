#![allow(unused_macros, unused_imports, unused)]
use std::f64::consts::PI;
const TAU: f64 = 2.0 * PI;

const R: i64 = 1_000_000_000;

use std::io::{Read, BufRead};
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn read_sigma<R: BufRead>(mut rdr: R) -> f64 {
    let mut buf = String::new();
    rdr.read_line(&mut buf).expect("read_sigma: failed to read line");
    let buf = buf.trim_end_matches('\n');

    buf.parse::<f64>().expect("read_sigma: failed to parse")
}

#[derive(Debug, Clone, Copy)]
enum Response {
    Dir(f64),
    Hit(i64, i64),
    Finish(i64, i64),
}

impl Response {
    fn dir(&self) -> f64 {
        match self {
            Self::Dir(t) => *t,
            _ => panic!(),
        }
    }
    fn same_dir(&self, other: &Self) -> bool {
        let thresh = PI / 6.0;
        match (self, other) {
            (Self::Dir(t0), Self::Dir(t1)) => {
                (t0 - t1).abs() < thresh || (t0 - t1 + TAU).abs() < thresh || (t0 - t1 - TAU).abs() < thresh
            }
            _ => false,
        }
    }

    fn opposite_dir(&self, other: &Self) -> bool {
        let thresh = PI / 6.0;
        match (self, other) {
            (Self::Dir(t0), Self::Dir(t1)) => {
                (t0 - t1 + PI).abs() < thresh || (t0 - t1 - PI).abs() < thresh
            }
            _ => false,
        }
    }
}

fn read_response<R: BufRead>(mut rdr: R) -> Response {
    let mut buf = String::new();
    rdr.read_line(&mut buf).expect("read_response: failed to read line");
    let buf = buf.trim_end_matches('\n');

    let mut it = buf.split_ascii_whitespace();

    let kind = it.next().expect("read_response: insufficient items (0)");
    let kind = kind.parse::<i32>().expect("read_response: failed to parse first item as i32");
    if kind == 0 {
        let dir = it.next().expect("read_response: insufficient items (1)");
        let dir = dir.parse::<f64>().expect("read_response: failed to parse second item as f64");
        Response::Dir(dir)
    } else {
        assert!(kind <= 2);
        let x = it.next().expect("read_response: insufficient items (1)");
        let x = x.parse::<i64>().expect("read_response: faield to parse second item as i64");
        let y = it.next().expect("read_response: insufficient items (2)");
        let y = y.parse::<i64>().expect("read_response: faield to parse third item as i64");

        if kind == 1 {
            Response::Hit(x, y)
        } else {
            Response::Finish(x, y)
        }
    }
}

fn main() {
    let stdin = std::io::stdin();
    let mut rdr = stdin.lock();
    let sigma = read_sigma(&mut rdr);

    let n_query = 1000;
    let mut s = State::new(sigma);

    for _ in 0..n_query {
        let q = s.next_query();
        println!("{} {}", q.x, q.y);

        let r = read_response(&mut rdr);
        match r {
            Response::Finish(..) => { break; }
            _ => {}
        }

        s.push(r);
    }
}

#[derive(Debug, Clone, Copy)]
struct Query {
    x: i64,
    y: i64,
}

impl Query {
    fn new(x: i64, y: i64) -> Self {
        assert!(x*x + y*y <= R.pow(2), "x={}, y={}, norm2={}", x, y, x*x + y*y);
        Self { x, y }
    }
    fn random() -> Self {
        let r: f64 = rand::random::<f64>() * R as f64;
        let t: f64 = rand::random::<f64>() * 2.0 * PI;

        Self::new((r * t.cos()) as i64, (r * t.sin()) as i64)
    }
    fn midpoint(&self, other: &Self) -> Self {
        Self {
            x: (self.x + other.x) / 2,
            y: (self.y + other.y) / 2,
        }
    }

    fn dist2(&self, other: &Self) -> i64 {
        (self.x - other.x).pow(2) + (self.y - other.y).pow(2)
    }

    fn mov(&self, dir: f64, dist: f64) -> Self {
        let x = self.x + (dist * dir.cos()) as i64;
        let y = self.y + (dist * dir.sin()) as i64;
        if x*x + y*y <= R.pow(2) {
            Self::new(x, y)
        } else {
            let x0 = self.x as f64;
            let y0 = self.y as f64;
            let b = x0 * dir.cos() + y0 * dir.sin();
            let c = x0 * x0 + y0 * y0 - (R * R) as f64;
            let (_, k) = solve_quad2(1.0, b, c);
            let k = k - 10.0;
    
            let x1 = x0 + k * dir.cos();
            let y1 = y0 + k * dir.sin();
    
            Self::new(x1 as i64, y1 as i64)
        }
    }
}

struct State {
    sigma: f64,
    sigma2: f64,
    turn: i64,
    hist: Vec<(Query, Response)>,
    not_found: Vec<(Query, Response, f64)>,
    between: [Option<(Query, Response)>; 2],
    next: Query,
    err: bool,
    found_targets: Vec<(i64, i64)>,
}

fn o(msg: &str) {
    println!("# {}", msg);
}

fn c(x: i64, y: i64, r: u32, g: u32, b: u32) {
    println!("#c {} {} {} {} {}", x, y, r, g, b)
}

impl State {
    fn new(sigma: f64) -> Self {
        State {
            sigma,
            sigma2: sigma.powi(2),
            turn: 0,
            hist: vec![],
            not_found: vec![],
            between: [None, None],
            next: Query::random(),
            err: false,
            found_targets: vec![],
        }
    }

    fn error(&mut self) -> Query {
        self.err = true;
        Query::new(0, 0)
    }

    fn next_query(&mut self) -> Query {
        if self.err {
            self.error()
        } else {
            self.next
        }
    }

    fn push(&mut self, r: Response) {
        self.turn += 1;
        o(&format!("turn={}", self.turn));
        let q = self.next;
        self.hist.push((q, r));

        if let Response::Hit(x, y) = r {
            self.found_targets.push((x, y));

            self.remove_found();

            self.next = if let Some(n) = self.find_between() {
                n
            } else {
                self.find_unbiguous()
            };
            o(&format!("next={:?}", &self.next));
            return;
        }

        self.push_not_found(q, r);

        if self.not_found.len() < 10000 {
            self.next = self.next_from_between(q, r);
        } else {
            self.next = todo!();
        }

    }

    fn between_edge(&self, q: Query, r: Response) -> (Query, f64) {
        let t0 = r.dir();

        let x0 = q.x as f64;
        let y0 = q.y as f64;
        let rad = R as f64;
        let b = x0 * t0.cos() + y0 * t0.sin();
        let c = x0 * x0 + y0 * y0 - rad * rad;
        let (_, k) = solve_quad2(1.0, b, c);
        let k = k - 10.0;

        let x1 = x0 + k * t0.cos();
        let y1 = y0 + k * t0.sin();

        assert!((x1*x1 + y1*y1 - rad*rad).abs() / (rad * rad) < 1e-4);
        (Query::new(x1 as i64, y1 as i64).midpoint(&q), k)
    }

    fn remove_found(&mut self) {
        let mut not_found = vec![];
        let dist_threshold = 3.0;
        let target = self.found_targets.last().unwrap();

        for &(q, r, min_dist) in &self.not_found {
            let dist = min_dist.min(self.normalized_dist(q, r, *target));
            // self.d(&format!("q={:?}, r={:?}, dist={}", q, r, dist));
            if dist_threshold < dist {
                not_found.push((q, r, dist));
            }
        }

        o(&format!("not_found.len()={:?}", not_found.len()));
        self.not_found = not_found;

    }

    fn find_between(&mut self) -> Option<Query> {
        let mut between = None;
        let mut ret = None;
        let mut score = 0;
        let thresh = 3.0 * self.sigma;
        for i in 0..self.not_found.len() {
            for j in i+1..self.not_found.len() {
                let r0 = self.not_found[i].1;
                let r1 = self.not_found[j].1;
                if r0.opposite_dir(&r1) {
                    let q0 = self.not_found[i].0;
                    let q1 = self.not_found[j].0;
                    let t0 = r0.dir();
                    let t1 = r1.dir();
                    let t2 = ((q0.y - q1.y) as f64).atan2((q0.x - q1.x) as f64);

                    if (t1 - t2).abs().min((t1 - t2 + TAU).abs()).min((t1 - t2 - TAU).abs()) < thresh {
                        let s = q0.dist2(&q1);
                        if s < score {
                            between = Some([Some((q0, r0)), Some((q1, r1))]);
                            ret = Some(q0.midpoint(&q1));
                            score = s;
                        }
                    }
                }
            }
        }

        if ret.is_some() {
            o("find_between");
        }

        ret
    }

    fn find_unbiguous(&mut self) -> Query {
        if self.not_found.is_empty() {
            self.between = [None, None];
            Query::random()
        } else {
            // if let Some(&(q, r, _)) = self.not_found.iter().filter(|(_, _, d)| *d > PI / 4.0).min_by_key(|(q, r, _)| {
            //     let k = self.between_edge(*q, *r).1 as i64;
            //     o(&format!("k={}", k));
            //     k
            // }) {
            //     self.between = [Some((q, r)), None];
            //     return self.between_edge(q, r).0
            // }

            // let mut farthest = self.not_found.iter_mut().max_by_key(|(_, _, l)| *l as i64).unwrap();
            // self.between = [Some((farthest.0, farthest.1)), None];
            // farthest.2 /= 2.0;
            // let (q, r, _) = *farthest;
            // self.between_edge(q, r).0

            let idx = rand::random::<usize>() % self.not_found.len();
            let (q, r, _) = self.not_found[idx];
            self.between = [Some((q, r)), None];
            self.between_edge(q, r).0
        }
    }

    fn normalized_dist(&self, q: Query, r: Response, target: (i64, i64)) -> f64 {
        let dx = (target.0 - q.x) as f64;
        let dy = (target.1 - q.y) as f64;

        let ta = dy.atan2(dx);
        let tb = r.dir();
        // self.d(&format!("ta={}, tb={}", ta, tb));

        let diff = (ta-tb).abs().min((ta-tb+TAU).abs()).min((ta-tb-TAU).abs());
        // self.d(&format!("diff={}", diff));

        // let p = 0.5 + 0.5 * erf(-diff / (self.sigma * 2.0f64.sqrt()));

        diff / self.sigma
    }

    fn next_from_between(&mut self, q: Query, r: Response) -> Query {
        let reset_thresh = 30_000_000i64.pow(2);
        let midpoint_thresh = 5_000_000i64.pow(2);

        match self.between {
            [None, None] => {
                self.between[0] = Some((q, r));
                self.between_edge(q, r).0
            }
            [Some((_, r0)), None] if r0.same_dir(&r) => {
                self.between[0] = Some((q, r));
                self.between_edge(q, r).0
            }
            [Some((q0, r0)), None] if r0.opposite_dir(&r) => {
                self.between[1] = Some((q, r));
                q0.midpoint(&q)
            }
            [Some((q0, r0)), None] if reset_thresh < q0.dist2(&q) => {
                q0.midpoint(&q)
            }
            [Some(_), None] => {
                self.between[0] = Some((q, r));
                self.between_edge(q, r).0
            }
            [Some((q0, r0)), Some((q1, r1))]
            if r0.same_dir(&r) && midpoint_thresh < q1.dist2(&q) => {
                self.between = [Some((q1, r1)), Some((q, r))];
                q1.midpoint(&q)
            }
            [Some((q0, r0)), Some((q1, r1))]
            if r1.same_dir(&r) && midpoint_thresh < q0.dist2(&q) => {
                self.between[1] = Some((q, r));
                q0.midpoint(&q)
            }
            [Some((q0, r0)), Some((q1, r1))] => {
                self.between = [Some((q, r)), None];
                
                let d = (q0.dist2(&q1) as f64).sqrt();
                q.mov(r.dir(), d / 4.0)

            }
            [None, Some(_)] => unreachable!()
        }
    }

    fn next_from_groups(&mut self, q: Query, r: Response) -> Query {
        let mut cands = vec![];
        for i in 0..self.not_found.len() {
            for j in i+1..self.not_found.len() {
                let a = self.not_found[i];
                let b = self.not_found[j];
                if let Some(d) = disjoint(a.0, a.1, b.0, b.1) {
                    cands.push(d);
                }
            }
        }

        todo!()
    }

    fn push_not_found(&mut self, q: Query, r: Response) {
        let dist_threshold = 3.0;
        let mut min_dist = std::f64::MAX;
        for &target in &self.found_targets {
            min_dist = min_dist.min(self.normalized_dist(q, r, target));
        }
        if dist_threshold < min_dist {
            self.not_found.push((q, r, min_dist));
        }
    }

}

fn erf(x: f64) -> f64 {
    let k = 40;
    if x.abs() < 2.4 {
        let mut c = 1.0;
        let mut a = 0.0;
        for i in 1..=k {
            a += x * c / (2 * i - 1) as f64;
            c = -c * x * x / i as f64
        }
        a * 2.0 / PI.sqrt()
    } else {
        let mut a;
        if x.abs() > 1e50 {
            a = 1.0;
        } else {
            let y = x.abs() * 2.0f64.sqrt();
            a = 0.0;
            for i in (1..=k).rev() {
                a = i as f64 / (y + a);
            }
            a = 1.0 - (-x * x).exp() / (y + a) * (2.0 / PI).sqrt();
        }
        if x < 0.0 {
            -a 
        } else {
            a
        }
    }
}

fn disjoint(q0: Query, r0: Response, q1: Query, r1: Response) -> Option<Query> {
    let t0 = r0.dir();
    let t1 = r1.dir();
    let x0 = q0.x as f64;
    let y0 = q0.y as f64;
    let x1 = q1.x as f64;
    let y1 = q1.y as f64;

    let k = 1.0 / (- t0.cos() * t1.sin() + t0.sin() * t1.cos()) * (-t1.sin() * (x1 - x0) + t1.cos() * (y1 - y0));
    if k > 0.0 {
        let x = x0 + t0.cos() * k;
        let y = y0 + t0.sin() * k;

        Some(Query::new(x as i64, y as i64))
    } else {
        None
    }
}


/// root of quadratic equation x.0 <= x.1
fn solve_quad2(a: f64, b: f64, c: f64) -> (f64, f64) {
    // let eps = 1e-6;
    let d = b * b - a * c;
    // if (a * c).abs() < eps {
    if b > 0.0 {
        ((-b-d.sqrt()) / a, c / (-b-d.sqrt()))
    } else{
        (c / (-b+d.sqrt()), (-b+d.sqrt()) / a)
    }
    // } else { ]
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_solve_quad2() {
        let a = 1.0;
        let b = 100.0;
        let c = 20.0;

        let (x0, x1) = solve_quad2(a, b, c);
        dbg!(x0, x1);
        assert!(dbg!(a * x0 * x0 + 2.0 * b * x0 + c) <= 1e-4);
        assert!(dbg!(a * x1 * x1 + 2.0 * b * x1 + c) <= 1e-4);
    }
}