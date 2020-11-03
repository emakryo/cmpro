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

#include<bits/stdc++.h>

template <typename T, typename E>
struct LazySegmentTree{
    std::vector<T> data, lazy;
    T def;
    E lazy_def;
    int n, height;
    LazySegmentTree(int n_, T def, E lazy_def): def(def), lazy_def(lazy_def){
        init(n_);
    }
    LazySegmentTree(const std::vector<T> &v, T def, E lazy_def): def(def), lazy_def(lazy_def){
        int n_ = v.size();
        init(n_);
        for(int i=0; i<n_; i++) data[n+i] = v[i];
        for(int i=n-1; i; i--) data[i] = merge(data[(i<<1)], data[(i<<1)|1]);
    }
    void init(int n_){
        n=1; height=0;
        while(n<n_) n<<=1, height++;
        data.assign(2*n, def);
        lazy.assign(2*n, lazy_def);
    }
    T reflect(int k){
        return lazy[k]==lazy_def?data[k]:apply(data[k], lazy[k]);
    }
    void eval(int k){
        if(lazy[k]==lazy_def) return;
        lazy[k<<1] = propagate(lazy[k<<1], lazy[k]);
        lazy[(k<<1)|1] = propagate(lazy[(k<<1)|1], lazy[k]);
        data[k] = reflect(k);
        lazy[k] = lazy_def;
    }
    void thrust(int k){
        for(int i=height; i; i--) eval(k>>i);
    }
    void recalc(int k){
        while(k>>=1) data[k] = merge(reflect(k<<1), reflect((k<<1)|1));
    }
    void update(int a, int b, E x){
        thrust(a+=n);
        thrust(b+=n-1);
        for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
            if(l&1) lazy[l] = propagate(lazy[l], x), l++;
            if(r&1) --r, lazy[r]=propagate(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }
    void set(int a, T x){
        thrust(a+=n);
        data[a] = x;
        lazy[a] = lazy_def;
        recalc(a);
    }
    T query(int a, int b){
        thrust(a+=n);
        thrust(b+=n-1);
        T vl = def, vr = def;
        for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
            if(l&1) vl = merge(vl, reflect(l++));
            if(r&1) vr = merge(reflect(--r), vr);
        }
        return merge(vl, vr);
    }

    T merge(T left, T right) const { return left+right; }
    E propagate(E before, E change) const { return before+change; }
    T apply(T val, E laz) const { return val+laz; }
};

using mi = mint<998244353>;

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> rs(k);
    for(int i=0; i<k; i++){
        cin >> rs[i].first >> rs[i].second;
        rs[i].second++;
    }

    LazySegmentTree<mi, mi> st(n, mi(0), mi(0));
    st.set(0, mi(1));
    for(int i=0; i<n-1; i++){
        mi a = st.query(i, i+1);
        dbg(i, a);
        for(int j=0; j<k; j++){
            if(i+rs[j].first>=n) continue;
            st.update(i+rs[j].first, min(i+rs[j].second, n), a);
        }
    }

    cout << st.query(n-1, n) << endl;;

    return 0;
}