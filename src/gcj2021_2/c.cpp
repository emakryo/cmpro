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
// Find (x, y)
// where
//   - a*x + b*y = gcd(a, b)$
long long ext_gcd(long long a, long long b, long long &x, long long &y){
    if(b == 0){
        x = 1; y = 0; return a;
    }
    long long nx, ny;
    long long g = ext_gcd(b, a%b, nx, ny);
    x = ny;
    y = nx - a / b * ny;
    return g;
}

template<long long m=1000000007>
struct modint {
    typedef long long ll;
    ll x;
    static constexpr ll mod() { return m; }
    constexpr modint(ll x=0): x((m+x%m)%m) {}
    modint<m> operator-() const { return modint(m-x); }
    modint<m>& operator+=(const modint<m> o) { x=(x+o.x)%m; return *this; }
    modint<m>& operator+=(const ll o) { return (*this)+=modint(o); }
    modint<m>& operator-=(const modint<m> o) { return (*this)+=(-o); }
    modint<m>& operator-=(const ll o) { return (*this)-=modint(o); }
    modint<m>& operator*=(const modint<m> o) { x = x*o.x%m; return *this; }
    modint<m>& operator*=(const ll o) { return (*this)*=modint(o); }
    modint<m>& operator/=(const modint<m> o) { return (*this)*=o.inv(); }
    modint<m>& operator/=(const ll o) { return (*this)/=modint(o); }
    friend modint<m> operator+(modint<m> l, const modint<m> r) { l+=r; return l; }
    friend modint<m> operator+(modint<m> l, const ll r) { l+=r; return l; }
    friend modint<m> operator+(const ll l, modint<m> r) { r+=l; return r; }
    friend modint<m> operator-(modint<m> l, const modint<m> r) { l-=r; return l; }
    friend modint<m> operator-(modint<m> l, const ll r) { l-=r; return l; }
    friend modint<m> operator-(const ll l, modint<m> r) { r*=-1; r+=l; return r; }
    friend modint<m> operator*(modint<m> l, const modint<m> r) { l*=r; return l; }
    friend modint<m> operator*(modint<m> l, const ll r) { l*=r; return l; }
    friend modint<m> operator*(const ll l, modint<m> r) { r*=l; return r; }
    friend modint<m> operator/(modint<m> l, const modint<m> r) { l/=r; return l; }
    friend modint<m> operator/(modint<m> l, const ll r) { l/=r; return l; }
    friend modint<m> operator/(const ll l, const modint<m> r) { return modint(l)/r; }
    bool operator==(const modint<m> o) const { return x==o.x; }
    bool operator!=(const modint<m> o) const { return x!=o.x; }
    friend bool operator==(const ll l, const modint<m> r) { return modint<m>(l) == r; }
    friend bool operator!=(const ll l, const modint<m> r) { return modint<m>(l) != r; }
    friend std::ostream& operator<<(std::ostream &os, const modint<m> x) { return os << x.x; }

    modint<m> pow(ll k) const {
        if(k==0) return modint<m>(1);
        if(k%2) return pow(k-1)*x;
        modint<m> z = pow(k/2); return z*z;
    }

    modint<m> inv() const {
        ll y,z;
        ext_gcd(x, m, y, z);
        return modint<m>(y);
    }
};

using mint = modint<>;

template<typename mint = mint>
struct Comb {
    typedef long long ll;
    const ll m = mint::mod();
    std::vector<mint> fact, fact_inv;
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
    mint operator() (ll n, ll k) const {
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
    mint fact_ext(ll n, ll &e) const {
        if(n == 0){
            e = 0;
            return mint(1);
        }

        mint na = fact_ext(n/m, e);
        e += n/m;
        mint a = na * fact[n%m];
        if((n/m)%2) a = a * (m-1);
        return a;
    }

// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
    mint comb_ext (ll n, ll k) const {
        ll e1,e2,e3;
        mint a1 = fact_ext(n, e1);
        mint a2 = fact_ext(k, e2);
        mint a3 = fact_ext(n-k, e3);

        if(e1 > e2+e3) return 0;
        else return a1*(a2*a3).inv();
    }
};

#include<bits/stdc++.h>

template <typename T>
struct SegmentTree{
    std::vector<T> v;
    T def;
    int n;
    SegmentTree(int n_, T default_value): def(default_value){
        n = 1;
        while(n<n_) n <<= 1;
        v.assign(2*n-1, def);
    }
    template<class I>
    SegmentTree(I first, I last, T default_value): SegmentTree(last-first, default_value){
        copy(first, last, v.begin()+n-1);
        for(int i=n-2; i>=0; i--)
            v[i] = merge(v[2*i+1], v[2*i+2]);
    }
    SegmentTree(std::vector<T> initial_data, T default_value):
    SegmentTree(initial_data.begin(), initial_data.end(), default_value){}
    // 0 <= idx < n
    void update(int idx, T val){
        idx += n-1;
        v[idx] = val;
        while(idx > 0){
            idx = (idx-1)/2;
            v[idx] = merge(v[2*idx+1], v[2*idx+2]);
        }
    }
    T q(int a, int b, int k, int l, int r){
        if(a<=l&&r<=b) return v[k];
        if(b<=l||r<=a) return def;
        return merge(q(a, b, 2*k+1, l, (l+r)/2), q(a, b, 2*k+2, (l+r)/2, r));
    }
    // 0 <= a < b < n
    T query(int a, int b){
        return q(a, b, 0, 0, n);
    }
    T merge(T left, T right);
};

// Example

template <typename T>
T SegmentTree<T>::merge(T a, T b){
    return std::max(a, b);
}

Comb<> c(200000);

mint rec(int s, int t, int b, SegmentTree<pair<int, int>> &v){
    if(t-s==0) return mint(1);
    pair<int, int> p = v.query(s, t);
    int m = p.second;
    dbg(s, t, b, m, p.first);
    if(-p.first != b) return 0;
    return c(t-s-1, m-s) * rec(s, m, b, v) * rec(m+1, t, b+1, v);
}

void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    cin >> v;

    SegmentTree<pair<int, int>> st(n, {-1e9, -1e9});
    for(int i=0; i<n; i++){
        st.update(i, {-v[i], i});
    }
    cout << rec(0, n, 1, st) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }

    return 0;
}