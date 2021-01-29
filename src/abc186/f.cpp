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

    int h, w, m; cin >> h >> w >> m;
    vector<int> x(m), y(m);
    for(int i=0; i<m; i++) cin >> x[i] >> y[i];

    vector<vector<int>> a(h), b(w);
    for(int i=0; i<m; i++){
        a[x[i]-1].push_back(y[i]-1);
        b[y[i]-1].push_back(x[i]-1);
    }

    for(int i=0; i<h; i++) sort(a[i].begin(), a[i].end());
    for(int i=0; i<w; i++) sort(b[i].begin(), b[i].end());

    Bit<int> p(h+1);
    int k = b[0].size()==0?h:b[0][0];
    for(int i=0; i<k; i++){
        p.add(i+1, 1);
    }
    ll ans = k;

    int l = a[0].size()==0?w:a[0][0];
    for(int i=1; i<l; i++){
        if(b[i].size()==0){
            ans += h;
        } else {
            ans += b[i][0];

            for(int x: b[i]){
                if(p.sum(x+1)-p.sum(x)>0) p.add(x+1, -1);
            }

            ans += p.sum(h) - p.sum(b[i][0]);
        }
    }

    for(int i=0; i<k; i++){
        if(p.sum(i+1)-p.sum(i) == 0) continue;

        if(a[i].size()==0){
            ans += w-l;
        } else {
            ans += a[i][0]-l;
        }
    }

    cout << ans << endl;

    return 0;
}