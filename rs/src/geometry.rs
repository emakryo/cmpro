// Point
pub type P = num_complex::Complex64; 
// Line (or segment)
pub type L = (P, P);
// Circle
pub type C = (P, f64);
const EPS: f64 = 1e-8;

pub fn cross(a: P, b: P) -> f64 {
    (a.conj() * b).im
}
pub fn dot(a: P, b: P) -> f64 {
    (a.conj() * b).re
}
pub fn ccw(a: P, b: P, c:P) -> i32 {
    let b = b-a;
    let c = c-a;
    if cross(b, c) > 0.into() { 1 } // counter clockwise
    else if cross(b, c) < 0.into() { -1 } // clockwise
    else if dot(b, c) < 0.into() { 2 } // c -- a -- b on line
    else if b.norm_sqr() < c.norm_sqr() { -2 } // a -- b -- c on line (including a == b)
    else { 0 } // a -- c -- b on line (including b == c and a == c)
}
/// Line and point
pub fn intersect_lp(line: L, point: P) -> bool {
    cross(line.0-point, line.0-point).abs() < EPS
}
/// Line and line
pub fn intersect_ll(l: L, m: L) -> bool {
    // non-parallel or same line
    cross(l.1-l.0, m.1-m.0).abs() > EPS || cross(l.1-l.0, m.0-l.0).abs() < EPS
}
/// Line and segment
pub fn intersect_ls(line: L, segment: L) -> bool {
    cross(line.1-line.0, segment.0-line.0) * cross(line.1-line.0, segment.1-line.0) < EPS
}
/// Segment and Segment
pub fn intersect_ss(s: L, t: L) -> bool {
    ccw(s.0, s.1, t.0) * ccw(s.0, s.1, t.1) <= 0 &&
        ccw(t.0, t.1, s.0) * ccw(t.0, t.1, s.1) <= 0
}
/// Segment and point
pub fn intersect_sp(segment: L, point: P) -> bool {
    // triangular inequality
    (segment.0-point).norm() + (segment.1-point).norm() - (segment.1-segment.0).norm() < EPS
}
pub fn projection(l: L, p: P) -> P {
    let t = dot(p-l.0, l.0-l.1) / (l.0 - l.1).norm();
    l.0 + t * (l.0 - l.1)
}

pub fn convex_hull(points: &[P]) -> Vec<P> {
    assert!(points.len() >= 3);
    let mut ps = points.to_owned();
    ps.sort_by(|a, b| if a.re != b.re {
        a.re.partial_cmp(&b.re).unwrap()
    } else {
        a.im.partial_cmp(&b.im).unwrap()
    });

    let mut hull = vec![];
    for &p in &ps {
        while hull.len() >= 2 && ccw(hull[hull.len()-2], hull[hull.len()-1], p) <= 0 {
            hull.pop();
        }
        hull.push(p);
    }
    let m = hull.len();
    for &p in ps.iter().rev().skip(1) {
        while hull.len() >= m+1 && ccw(hull[hull.len()-2], hull[hull.len()-1], p) <= 0 {
            hull.pop();
        }
        hull.push(p);
    }

    hull
}