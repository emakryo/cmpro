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
long long crossing(std::vector<int> &v){
    Bit<long long> bit(v.size()+1);
    long long count = 0;
    for(int i=0; i<v.size(); i++){
        count += i - bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m; cin >> n >> m;
    vector<vector<int>> lr(n);
    for(int i=0; i<m; i++){
        int l, r;
        l--; r--;
        cin >> l >> r;
        if(l>r) swap(l, r);
        lr[l].push_back(r);
    }

    Bit<int> bit(n+1);

    ll ans = 0;
    for(int i=0; i<n; i++){
        for(int r: lr[i]){
            ans += bit.sum(r) - bit.sum(i+1);
        }

        for(int r: lr[i]){
            bit.add(r+1, 1);
        }
    }

    cout << ans << endl;


    return 0;
}