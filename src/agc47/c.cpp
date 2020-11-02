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

// Extended Euclid's greatest common divisor algorithm
// Find (x, y, g)
// where a*x + b*y = g$ and g is the greatest common divisor of (a, b)
long long ext_gcd(long long a, long long b, long long &x, long long &y){
    if(b == 0){
        x = 1; y = 0; return a;
    }
    long long nx, ny;
    long long g = ext_gcd(b, a%b, nx, ny);
    x = ny; y = nx - a/b *ny;
    return g;
}

template<long long m=1000000007>
struct mint {
    typedef long long ll;
    ll x;
    static constexpr ll mod() { return m; }
    constexpr mint(ll x=0): x((m+x%m)%m) {}
    mint<m> operator-() const { return mint(m-x); }
    mint<m>& operator+=(const mint<m> o) { x=(x+o.x)%m; return *this; }
    mint<m>& operator+=(const ll o) { return (*this)+=mint(o); }
    mint<m>& operator-=(const mint<m> o) { return (*this)+=(-o); }
    mint<m>& operator-=(const ll o) { return (*this)-=mint(o); }
    mint<m>& operator*=(const mint<m> o) { x = x*o.x%m; return *this; }
    mint<m>& operator*=(const ll o) { return (*this)*=mint(o); }
    mint<m>& operator/=(const mint<m> o) { return (*this)*=o.inv(); }
    mint<m>& operator/=(const ll o) { return (*this)/=mint(o); }
    friend mint<m> operator+(mint<m> l, const mint<m> r) { l+=r; return l; }
    friend mint<m> operator+(mint<m> l, const ll r) { l+=r; return l; }
    friend mint<m> operator+(const ll l, mint<m> r) { r+=l; return r; }
    friend mint<m> operator-(mint<m> l, const mint<m> r) { l-=r; return l; }
    friend mint<m> operator-(mint<m> l, const ll r) { l-=r; return l; }
    friend mint<m> operator-(const ll l, mint<m> r) { r-=l; return r; }
    friend mint<m> operator*(mint<m> l, const mint<m> r) { l*=r; return l; }
    friend mint<m> operator*(mint<m> l, const ll r) { l*=r; return l; }
    friend mint<m> operator*(const ll l, mint<m> r) { r*=l; return r; }
    friend mint<m> operator/(mint<m> l, const mint<m> r) { l/=r; return l; }
    friend mint<m> operator/(mint<m> l, const ll r) { l/=r; return l; }
    friend mint<m> operator/(const ll l, const mint<m> r) { return mint(l)/r; }
    bool operator==(const mint<m> o) const { return x==o.x; }
    bool operator!=(const mint<m> o) const { return x!=o.x; }
    friend bool operator==(const ll l, const mint<m> r) { return mint<m>(l) == r; }
    friend bool operator!=(const ll l, const mint<m> r) { return mint<m>(l) != r; }
    friend std::ostream& operator<<(std::ostream &os, const mint<m> x) { return os << x.x; }

    mint<m> pow(ll k) const {
        if(k==0) return mint<m>(1);
        if(k%2) return pow(k-1)*x;
        mint<m> z = pow(k/2); return z*z;
    }

    mint<m> inv() const {
        ll y,z;
        ext_gcd(x, m, y, z);
        return mint<m>(y);
    }
};

template<long long m=1000000007>
struct Comb {
    typedef long long ll;
    std::vector<mint<m>> fact, fact_inv;
    Comb(int n_max=2000005) {
        fact.assign(n_max, 0);
        fact_inv.assign(n_max, 0);
        fact[0] = 1;
        fact_inv[0] = 1;
        for(int i=1; i<std::min((ll)n_max, m); i++){
            fact[i] = fact[i-1] * i;
            fact_inv[i] = fact[i].inv();
        }
    }
    mint<m> operator() (ll n, ll k) const {
        if(n < m){
            return fact[n] * fact_inv[k] * fact_inv[n-k];
        } else {
            return comb_ext(n, k);
        }
    }

// Modular factorial of n, also counting p's appearance e
// n! = a * p^e
// return: a % p
// n! = n * (n-1) * ... * (k*p+1) *
//      (k*p) * (k*p-1) * ... ((k-1)*p+1) *
//      ...
//      p * (p-1) * ... * 2 * 1   (k = floor(n/p))
//    = (n%p) * ... * 1 *
//      (k*p) * (p-1) * ... * 1 *
//      p * (p-1) * ... * 1       (mod p, preserving p's multiples)
//    = (n%p)! * p^k * k! * (p-1)^k
//    = (n%p)! * p^k * k! * (p-1)^(k%2)
//
// From the facts:
//   (p-1)! = p-1 (mod p) (c.f. Willson's theorem)
//   (p-2)**2 = 1 (mod p)
    mint<m> fact_ext(ll n, ll &e) const {
        if(n == 0){
            e = 0;
            return mint<m>(1);
        }

        mint<m> na = fact_ext(n/m, e);
        e += n/m;
        mint<m> a = na * fact[n%m];
        if((n/m)%2) a = a * (m-1);
        return a;
    }

// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
    mint<m> comb_ext (ll n, ll k) const {
        ll e1,e2,e3;
        mint<m> a1 = fact_ext(n, e1);
        mint<m> a2 = fact_ext(k, e2);
        mint<m> a3 = fact_ext(n-k, e3);

        if(e1 > e2+e3) return 0;
        else return a1*(a2*a3).inv();
    }
};

constexpr long long pow_mod(long long x, long long n, int m) {
    if(m==1) return 0;
    unsigned int um = m;
    long long y = ((x%um)+um)%um;
    unsigned long long r = 1;
    while(n){
        if(n&1) r = r*y%um;
        y = y*y%um;
        n >>= 1;
    }
    return r;
}

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

constexpr int find_primitive_root(int m){
    if(m==2) return 1;
    if(m==167772161) return 3;
    if(m==469762049) return 3;
    if(m==754974721) return 11;
    if(m==998244353) return 3;

    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m-1)/2;
    while(x%2==0) x /= 2;
    for(int i=3; (long long)(i)*i<=x; i+=2){
        if(x%i==0){
            divs[cnt++] = i;
            while(x%i==0){
                x /= i;
            }
        }
    }
    if(x>1){
        divs[cnt++] = x;
    }
    for(int g=2;; g++){
        bool ok = true;
        for(int i=0; i<cnt; i++){
            if (pow_mod(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

template<long long m>
constexpr mint<m> primitive_root = mint<m>(find_primitive_root(m));

int bsf(unsigned long long x){
    return __builtin_ctz(x);
}

int ceil_log2(unsigned long long x){
    int n = 0;
    while((1ULL<<n)<x) n++;
    return n;
}

template<typename mint>
void fft(std::vector<mint> &f) {
    static constexpr mint g = primitive_root<mint::mod()>;
    int n = f.size();
    int h = ceil_log2(n);
    assert(1<<h == n);

    static bool init = false;
    static mint sum_e[30];
    if(!init){
        init = true;
        mint es[30], ies[30];
        int cnt2 = bsf(mint::mod() - 1);
        assert(cnt2 >= h);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
    }
    for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = f[i + offset];
                auto r = f[i + offset + p] * now;
                f[i + offset] = l + r;
                f[i + offset + p] = l - r;
            }
            now *= sum_e[bsf(~(unsigned int)(s))];
        }
    }
}

template <typename mint>
void ifft(std::vector<mint> &f) {
    static constexpr mint g = primitive_root<mint::mod()>;
    int n = int(f.size());
    int h = ceil_log2(n);
    assert(1<<h == n);

    static bool init = false;
    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    if (!init) {
        init = true;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }

    for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = f[i + offset];
                auto r = f[i + offset + p];
                f[i + offset] = l + r;
                f[i + offset + p] =
                    (unsigned long long)(mint::mod() + l.x - r.x) *
                    inow.x;
            }
            inow *= sum_ie[bsf(~(unsigned int)(s))];
        }
    }

    mint z = mint(1<<h).inv();
    for(int i=0; i<f.size(); i++){
        f[i] *= z;
    }
}

template<typename mint>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b){
    int n = a.size(), m = b.size();
    if(std::min(n, m)<=60){
        if(n<m){
            std::swap(n, m);
            std::swap(a, b);
        }
        std::vector<mint> ans(n+m-1);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                ans[i+j] += a[i] * b[j];
            }
        }
        return ans;
    }

    int z = 1 << ceil_log2(n+m-1);
    a.resize(z);
    b.resize(z);
    fft(a);
    fft(b);
    for(int i=0; i<z; i++) a[i] *= b[i];
    ifft(a);
    a.resize(n+m-1);
    return a;
}

template<long long mod = 998244353>
std::vector<long long> convolution(std::vector<long long> a, std::vector<long long> b){
    using mi = mint<mod>;
    std::vector<mi> a2(a.size()), b2(b.size());
    for(int i=0; i<a.size(); i++) a2[i] = mi(a[i]);
    for(int i=0; i<b.size(); i++) b2[i] = mi(b[i]);

    auto c2 = convolution(move(a2), move(b2));
    int n = a.size() + b.size() - 1;
    std::vector<long long> c(n);
    for(int i=0; i<n; i++){
        c[i] = c2[i].x;
    }
    return c;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
    int n = a.size(), m = b.size();
    if (!n || !m) return {};

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr unsigned long long i1 = inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 = inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 = inv_gcd(MOD1 * MOD2, MOD3).second;

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        // B = 2^63, -B <= x, r(real value) < B
        // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
        // r = c1[i] (mod MOD1)
        // focus on MOD1
        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
        // r = x,
        //     x - M' + (0 or 2B),
        //     x - 2M' + (0, 2B or 4B),
        //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
        // (r - x) = 0, (0)
        //           - M' + (0 or 2B), (1)
        //           -2M' + (0 or 2B or 4B), (2)
        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
        // we checked that
        //   ((1) mod MOD1) mod 5 = 2
        //   ((2) mod MOD1) mod 5 = 3
        //   ((3) mod MOD1) mod 5 = 4
        long long M1 = MOD1;
        long long diff =
            c1[i] - ((long long)(x)%M1+M1)%M1;
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}

const int P = 200003;

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n; cin >> n;
    vector<int> a(n); cin >> a;

    vector<ll> w(P), f(P), g(P);
    vector<int> pos(P);
    ll w0 = 1;
    for(int i=0; i<P-1; i++){
        w[i] = w0;
        pos[w0] = i;
        w0 = w0*2%P;
    }

    for(int i=0; i<n; i++){
        if(a[i]==0) continue;
        f[pos[a[i]]]++;
        g[pos[a[i]]]++;
    }

    for(int i=0; i<P; i++){
        if(f[i]>0) dbg(i, f[i], w[i]);
    }

    vector<ll> c = convolution_ll(f, g);

    ll ans = 0;
    for(int i=0; i<c.size(); i++){
        if(c[i]>0) dbg(i, c[i], w[i%(P-1)]);
        ans += c[i]*w[i%(P-1)];
    }
    for(int i=0; i<n; i++){
        dbg((ll)a[i]*a[i]%P);
        ans -= (ll)a[i]*a[i]%P;
    }
    cout << ans/2 << endl;

    return 0;
}