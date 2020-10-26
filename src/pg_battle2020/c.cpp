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

struct mint {
    typedef long long ll;
    ll x, m;
    mint(ll x=0, ll m=1e9+7): x((m+x%m)%m), m(m) {}
    mint operator-() const { return mint(m-x, m); }
    mint& operator+=(const mint o) { x=(x+o.x)%m; return *this; }
    mint& operator+=(const ll o) { return (*this)+=mint(o, m); }
    mint& operator-=(const mint o) { return (*this)+=(-o); }
    mint& operator-=(const ll o) { return (*this)-=mint(o, m); }
    mint& operator*=(const mint o) { x = x*o.x%m; return *this; }
    mint& operator*=(const ll o) { return (*this)*=mint(o, m); }
    mint& operator/=(const mint o) { return (*this)*=o.inv(); }
    mint& operator/=(const ll o) { return (*this)/=mint(o, m); }
    friend mint operator+(mint l, const mint r) { l+=r; return l; }
    friend mint operator+(mint l, const ll r) { l+=r; return l; }
    friend mint operator+(const ll l, mint r) { r+=l; return r; }
    friend mint operator-(mint l, const mint r) { l-=r; return l; }
    friend mint operator-(mint l, const ll r) { l-=r; return l; }
    friend mint operator-(const ll l, mint r) { r-=l; return r; }
    friend mint operator*(mint l, const mint r) { l*=r; return l; }
    friend mint operator*(mint l, const ll r) { l*=r; return l; }
    friend mint operator*(const ll l, mint r) { r*=l; return r; }
    friend mint operator/(mint l, const mint r) { l/=r; return l; }
    friend mint operator/(mint l, const ll r) { l/=r; return l; }
    friend mint operator/(const ll l, const mint r) { return mint(l, r.m)/r; }
    bool operator==(const mint o) const { return x==o.x; }
    bool operator!=(const mint o) const { return x!=o.x; }
    friend bool operator==(const ll l, const mint r) { return mint(l, r.m) == r; }
    friend bool operator!=(const ll l, const mint r) { return mint(l, r.m) != r; }
    friend std::ostream& operator<<(std::ostream &os, const mint x) { return os << x.x; }

    mint pow(ll k) const {
        if(k==0) return mint(1, m);
        if(k%2) return pow(k-1)*x;
        mint z = pow(k/2); return z*z;
    }

    mint inv() const {
        ll y,z;
        ext_gcd(x, m, y, z);
        return mint(y, m);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    ll n, m, d; cin >> n >> m >> d;
    vector<ll> a(m); cin >> a;
    sort(a.begin(), a.end());

    map<ll, vector<ll>> mpos;
    for(int i=0; i<m; i++){
        a[i]--;
        mpos[a[i]%d].push_back(a[i]/d);
    }

    mint ans(0);
    ll nr0 = n%d;
    ll nr1 = d-n%d;

    for(auto p: mpos){
        ll s = 0;
        dbg(p.first, p.second);
        for(auto x: p.second){
            mint z(x-s);
            dbg(" ", x, z);
            ans += (z+1)*z/2;
            s = x+1;
        }
        if(p.first < n%d){
            nr0--;
            mint z(n/d-s+1);
            ans += (z+1)*z/2;
        } else {
            nr1--;
            mint z(n/d-s);
            dbg(" ", -1, s, z);
            ans += (z+1)*z/2;
        }
    }

    mint z(n/d);
    dbg(ans, z, nr0, nr1);
    ans += (z+1)*(z+2)/2*nr0;
    ans += z*(z+1)/2*nr1;

    cout << ans << endl;
    return 0;
}