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

    // Example (min, add)
    T merge(T left, T right) const { return std::max(left, right); }
    E propagate(E before, E change) const { return before+change; }
    T apply(T val, E laz) const { return val+laz; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, k; cin >> n >> k;
    vector<int> a(n); cin >> a;

    LazySegmentTree<int, int> st(300005, -1e9, 0);
    for(int i=0; i<n; i++){
        st.set(a[i], 1+max(0, st.query(max(0, a[i]-k), min(300005, a[i]+1+k))));
    }

    for(int i=0; i<20; i++){
        dbg(i, st.query(i, i+1));
    }

    cout << st.query(0, 300005) << endl;

    return 0;
}