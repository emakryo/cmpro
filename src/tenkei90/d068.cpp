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
    return a + b;
}

template<>
bool SegmentTree<bool>::merge(bool a, bool b){
    return a&&b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, q;
    cin >> n >> q;

    SegmentTree<ll> sum(n, 0);
    SegmentTree<bool> ok(n, true);

    for(int i=0; i<n; i++) ok.update(i, false);

    for(int i=0; i<q; i++){
        int t, x, y;
        ll v;
        cin >> t >> x >> y >> v;
        x--; y--;
        if(t==0){
            if(x%2) v = -v;
            sum.update(x, v);
            ok.update(x, true);
            dbg(t, x, v, sum.query(x, x+1));
        } else {
            ll a;
            if(x==y){
                a = v;
            } else if(x<y){
                ll z = sum.query(x, y);
                dbg(t, x, y, z, ok.query(x, y));
                if(!ok.query(x, y)) {
                    cout << "Ambiguous" << endl;
                    continue;
                }
                a = ((y-x)%2?-v:v) + (y%2?z:-z);
            } else {
                ll z = sum.query(y, x);
                dbg(t, x, y, z, ok.query(y, x));
                if(!ok.query(y, x)) {
                    cout << "Ambiguous" << endl;
                    continue;
                }
                a = ((x-y)%2?-v:v) + (y%2?-z:z);
            }

            cout << a << endl;
        }
    }
    return 0;
}