#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
    string sep = " ";
    if(v.size()) os << v[0];
    for(int i=1; i<v.size(); i++) os << sep << v[i];
    return os;
}

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

#include<bits/stdc++.h>

template<typename T>
struct Point {
    T x, y;
    Point(T x=0, T y=0):x(x), y(y) {}
    Point(std::pair<T, T> p): x(p.first), y(p.second) {}
    Point& operator+= (const Point &o){ x += o.x; y += o.y; return *this; }
    friend Point operator+ (Point x, const Point &y) { x += y; return x; }
    Point& operator-= (const Point &o){ x -= o.x; y -= o.y; return *this; }
    friend Point operator- (Point x, const Point &y) { x -= y; return x; }
    Point& operator*= (const T &a) { x *= a, y *= a; return *this; }
    friend Point operator* (const T a, Point x) { x *= a; return x; }
    Point& operator/= (const T &a) { x /= a, y /= a; return *this; }
    friend Point operator/ (Point x, const T a) { x /= a; return x; }
    T dot(const Point &o) const { return x*o.x+y*o.y; }
    T det(const Point &o){ return x*o.y-y*o.x; }
    // complex product
    Point cp(const Point &o) {
        std::complex<T> p = std::complex<T>(x, y) * std::complex<T>(o.x, o.y);
        return Point(p.real(), p.imag());
    }
    bool operator< (const Point &o) { return x<o.x || (x==o.x && y<o.y); };
};

template<typename T>
ostream& operator<<(ostream &os, Point<T> &p){
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

typedef Point<long long> PLL;
pair<std::vector<PLL>, vector<PLL>> convex_hull(std::vector<PLL> &points){
    int n = points.size();
    std::sort(points.begin(), points.end());
    std::vector<PLL> lower(n), upper(n);
    int l = 0, r = 0;
    for(auto p: points){
        while(l>1 && (lower[l-1]-lower[l-2]).det(p-lower[l-1]) <= 0) l--;
        lower[l++] = p;
    }

    for(int j=points.size()-1; j>=0; j--){
        auto p = points[j];
        while(r>1 && (upper[r-1]-upper[r-2]).det(p-upper[r-1]) <= 0) r--;
        upper[r++] = p;
    }

    // for(int j=1; j<r-1; j++) lower[l++] = upper[j];
    lower.resize(l);
    upper.resize(r);

    return {lower, upper};
}

typedef Point<double> P;
double dist2(P a, P b){
    return (a-b).dot(a-b);
}

// 外心, not tested well
P circumcenter(P a, P b, P c){
    double x = dist2(b, c);
    double y = dist2(a, c);
    double z = dist2(a, b);

    double p = x*(y+z-x);
    double q = y*(x+z-y);
    double r = z*(y+x-z);

    if(p+q+r < 1e-5){
        if(x >= y && x >= z){
            return 0.5 * (b + c);
        } else if(y >= x && y >= z){
            return 0.5 * (a + c);
        } else {
            return 0.5 * (a + b);
        }
    } else {
        return (p*a + q*b + r*c) / (p + q + r);
    }
}

std::vector<P> circles_intersections(P x1, double r1, P x2, double r2){
    P z = x2-x1;
    double d2 = dist2(z, P());
    double a = (d2 + r1*r1 - r2*r2)/2;
    double b2 = d2 * r1*r1 - a*a;
    double c = d2;
    if(abs(b2) < 1e-10){
        return {P(a * z.x / c, a * z.y / c) + x1};
    }
    if(b2 < 0) return std::vector<P>();

    double b = sqrt(b2);
    return {P((a * z.x + z.y * b) / c,
              (a * z.y - z.x * b) / c) + x1,
           P((a * z.x - z.y * b) / c,
             (a * z.y + z.x * b) / c) + x1};
}

#include<bits/stdc++.h>

long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = (a%b+b)%b;
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// (rem, mod)
std::pair<long long, long long> crt(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        long long m1 = m[i];
        long long r1 = (r[i]%m1+m1)%m1;
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        // assume: m0 > m1, lcm(m0, m1) >= 2 * max(m0, m1)

        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0, m1));
        // r2 % m0 = r0
        // r2 % m1 = r1
        // -> (r0 + x*m0) % m1 = r1
        // -> x*u0*g % (u1*g) = (r1 - r0) (u0*g = m0, u1*g = m1)
        // -> x = (r1 - r0) / g * inv(u0) (mod u1)

        // im = inv(u0) (mod u1) (0 <= im < u1)
        long long g, im;
        std::tie(g, im) = inv_gcd(m0, m1);

        long long u1 = (m1 / g);
        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)
        if ((r1 - r0) % g) return {0, 0};

        // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)
        long long x = (r1 - r0) / g % u1 * im % u1;

        // |r0| + |m0 * x|
        // < m0 + m0 * (u1 - 1)
        // = m0 + m0 * m1 / g - m0
        // = lcm(m0, m1)
        r0 += x * m0;
        m0 *= u1;  // -> lcm(m0, m1)
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<PLL> p(n);
    for(int i=0; i<n; i++){
        ll x, y;
        cin >> x >> y;
        p[i] = {x, y};
    }

    auto lu = convex_hull(p);
    map<ll, ll> lm, um;
    for(auto po: lu.first){
        if(lm.count(po.x)) lm[po.x] = min(lm[po.x], po.y);
        else lm[po.x] = po.y;
    }

    for(auto po: lu.second){
        if(um.count(po.x)) um[po.x] = max(um[po.x], po.y);
        else um[po.x] = po.y;
    }

    vector<PLL> lower, upper;
    for(auto pa: lm){
        lower.push_back({pa.first, pa.second});
    }
    for(auto pa: um){
        upper.push_back({pa.first, pa.second});
    }


    sort(lower.begin(), lower.end());
    sort(upper.begin(), upper.end());
    dbg(lower);
    dbg(upper);

    ll ans = 0;
    for(int i=0; i<upper.size()-1; i++){
        ll dx = upper[i+1].x - upper[i].x;
        ll dy = upper[i+1].y - upper[i].y;
        if(dx==0) continue;
        dbg(dx, dx, dy, dx*upper[i].y, dx*upper[i+1].y);
        ll x;
        if(dy>0) x = floor_sum(dx, dx, dy, dx*upper[i].y);
        else x = floor_sum(dx, dx, -dy, dx*upper[i+1].y-dy);

        dbg(upper[i], upper[i+1], x);
        ans += x;
    }

    ans += upper.back().y;
    dbg(ans);

    for(int i=0; i<lower.size()-1; i++){
        ll dx = lower[i+1].x-lower[i].x;
        ll dy = lower[i+1].y-lower[i].y;
        if(dx==0) continue;

        ll x;

        dbg(dx, dy, max(lower[i].y, lower[i+1].y)*dx);
        if(dy>=0) x = max(lower[i].y, lower[i+1].y)*dx - floor_sum(dx, dx, dy, dy+dx);
        else x = max(lower[i].y, lower[i+1].y)*dx - floor_sum(dx, dx, -dy, dx);
        dbg(lower[i], lower[i+1], x);
        ans -= x;
    }

    ans -= lower.back().y - 1;
    dbg(ans);

    cout << ans-n << endl;

    return 0;
}