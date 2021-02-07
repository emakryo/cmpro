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
    friend modint<m> operator-(const ll l, modint<m> r) { r-=l; return r; }
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

template<long long m=1000000007>
struct Comb {
    typedef long long ll;
    std::vector<modint<m>> fact, fact_inv;
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
    modint<m> operator() (ll n, ll k) const {
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
    modint<m> fact_ext(ll n, ll &e) const {
        if(n == 0){
            e = 0;
            return modint<m>(1);
        }

        modint<m> na = fact_ext(n/m, e);
        e += n/m;
        modint<m> a = na * fact[n%m];
        if((n/m)%2) a = a * (m-1);
        return a;
    }

// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
    modint<m> comb_ext (ll n, ll k) const {
        ll e1,e2,e3;
        modint<m> a1 = fact_ext(n, e1);
        modint<m> a2 = fact_ext(k, e2);
        modint<m> a3 = fact_ext(n-k, e3);

        if(e1 > e2+e3) return 0;
        else return a1*(a2*a3).inv();
    }
};

using mint = modint<998244353>;

int dfs(int u, vector<vector<int>> &g, vector<bool> &visit){
    visit[u] = true;
    int r = 1;
    for(int v=0; v<g[u].size(); v++){
        if(g[u][v]==0) continue;
        if(!visit[v]) r += dfs(v, g, visit);
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    Comb<998244353> comb;

    int n, k; cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i=0; i<n; i++) cin >> a[i];

    vector<vector<int>> gx(n, vector<int>(n)), gy(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            bool okx = true, oky = true;
            for(int l=0; l<n; l++){
                if(a[i][l]+a[j][l]>k) okx = false;
                if(a[l][i]+a[l][j]>k) oky = false;
            }

            if(okx) gx[i][j] = gx[j][i] = 1;
            if(oky) gy[i][j] = gy[j][i] = 1;
        }
    }

    for(auto g: gx) dbg(g);
    for(auto g: gy) dbg(g);

    mint ans = 1;
    vector<bool> vx(n), vy(n);
    for(int i=0; i<n; i++){
        if(!vx[i]) ans *= comb.fact[dfs(i, gx, vx)];
        if(!vy[i]) ans *= comb.fact[dfs(i, gy, vy)];
    }

    cout << ans << endl;

    return 0;
}