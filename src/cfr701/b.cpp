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

template <typename T>
struct Bit{
    std::vector<T> v;
    int n;
    Bit(int n_): n(n_){ v.assign(n_, 0); }
    // 0 <= i < n
    T sum(int i){
        T s=0;
        while(i>0){ s += v[i]; i -= i & -i; }
        return s;
    }
    // 1 <= i < n
    void add(int i, T x){
        while(i < n){ v[i] += x; i += i & -i; }
    }
};

// v: permutation of (1, ... , n)
int crossing(std::vector<int> &v){
    Bit<int> bit(v.size()+1);
    int count = 0;
    for(int i=0; i<v.size(); i++){
        count += i - bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, q, k; cin >> n >> q >> k;
    vector<int> a(n); cin >> a;

    Bit<ll> x(n+1);
    x.add(1, a[1]-1);
    x.add(n, k-a[n-1]-1);
    for(int i=1; i<n-1; i++){
        x.add(i+1, a[i+1]-a[i-1]-2);
    }

    for(int qq=0; qq<q; qq++){
        int l, r; cin >> l >> r;
        l--;
        if(r-l==1){
            cout << k-1 << endl;
        } else {
            ll b = a[l+1]-2;
            ll e = k-a[r-2]-1;
            ll m = r-l>2?x.sum(r-1)-x.sum(l+1):0;
            dbg(b, e, m);
            cout << m + b + e << endl;
        }
    }
    return 0;
}