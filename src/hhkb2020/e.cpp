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

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int h, w; cin >> h >> w;
    vector<string> s(h);
    for(int i=0; i<h; i++) cin >> s[i];

    vector<vector<int>> cx(h, vector<int>(w)), cy(h, vector<int>(w));
    int k = 0;
    for(int i=0; i<h; i++){
        int c = 0;
        for(int j=0; j<w; j++){
            if(s[i][j]=='.'){
                cx[i][j] = -c;
                cx[i][j-c] = c+1;
                c++;
                k++;
            } else {
                c = 0;
            }
        }
    }

    for(int j=0; j<w; j++){
        int c = 0;
        for(int i=0; i<h; i++){
            if(s[i][j]=='.'){
                cy[i][j] = -c;
                cy[i-c][j] = c+1;
                c++;
            } else {
                c = 0;
            }
        }
    }

    for(int i=0; i<h; i++){
        dbg(cx[i]);
    }

    for(int i=0; i<h; i++){
        dbg(cy[i]);
    }

    vector<mint<>> p2(h*w+1);
    p2[0] = 1;
    for(int i=1; i<h*w+1; i++){
        p2[i] = 2*p2[i-1];
    }

    mint<> ans(0);
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(s[i][j]=='#') continue;
            int n = -1;
            if(cx[i][j]<0) n += cx[i][j+cx[i][j]];
            else n += cx[i][j];
            if(cy[i][j]<0) n+= cy[i+cy[i][j]][j];
            else n += cy[i][j];
            dbg(i, j, n);

            ans += (p2[n]-1) * p2[k-n];
        }
    }

    cout << ans << endl;

    return 0;
}