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
// where
//   - a*x + b*y = g$
//   - g is the greatest common divisor of (a, b)
//   - x > 0, y <= 0
//   - x is minimum
long long ext_gcd(long long a, long long b, long long &x, long long &y){
    if(b == 0){
        x = 1; y = 0; return a;
    }
    long long nx, ny;
    long long g = ext_gcd(b, a%b, nx, ny);
    long long k = -ny/b+1;
    x = ny + k * b;
    y = nx - a / b * ny - k * a;
    assert(a*x+b*y==g);
    return g;
}

/*

ax + by = g

a%b = r
a/b = q
a = qb + r

bx' + (a%b)y' = g

(qb+r)x + by = g
by + rx + qbx = g
by + rx + qbx = g
b(y+qx) + rx = g

/ y+qx = x'
\ x = y'

/ x = y'
\ y = x' - q y'



*/

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    /*
    k(k+1)/2 == pN  <=> k(k+1) == 2pN
    p >= 1

    find min k

    upper bound; k=N-1

    2N|a
    2pN = 2pa(N/a)
    k|a || (k+1)|a

    k = qa, q >= 1
    qa(qa+1) = p(2N/a)
    q(qa+1) = p(2N/a)
    qa+1 | 2N/a
    qa + 1 = r(2N/a)
    r(2N/a) - qa = 1

    qa(qa-1) = p(2N/a);
    qa - 1 = r(2N/a);
    qa - r(2N/a) = 1

    */

    ll n; cin >> n;
    if(n==1){
        cout << 1 << endl;
        return 0;
    }

    ll ans = 1e18;
    for(ll a=2; a*a<=2*n; a++){
        if(2*n%a==0){
            ll q, r;
            ll g = ext_gcd(2*n/a, a, r, q);
            if(g==1){
                ans = min(ans, -q*a);
            }

            g = ext_gcd(a, 2*n/a, q, r);
            if(g==1){
                ans = min(ans, q*a-1);
            }
        }
    }
    cout << ans << endl;

    return 0;
}