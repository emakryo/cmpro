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
    return {a.first+b.first, a.second+b.second};
}

int n, m, q;
vector<int> ts, xs;
vector<ll> ys;
vector<ll> allans;

void solve();
void solve_naive();

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    cin >> n >> m >> q;
    for(int i=0; i<q; i++){
        int t, x;
        ll y;
        cin >> t >> x >> y;
        x--;
        ts.push_back(t);
        xs.push_back(x);
        ys.push_back(y);
    }

    // solve_naive();
    // vector<ll> naive_ans(allans);

    // allans.clear();
    solve();

    for(int i=0; i<allans.size(); i++){
        cout << allans[i] << endl;
    }
    return 0;
}

void solve_naive(){
    ll ans = 0;
    vector<ll> a(n), b(m);
    vector<vector<ll>> s(n, vector<ll>(m));
    for(int i=0; i<q; i++){
        int x = xs[i];
        ll y = ys[i];
        int t = ts[i];

        if(t==1){
            for(int j=0; j<m; j++){
                ll z = max(b[j], y);
                ans += z - s[x][j];
                s[x][j] = z;
            }
            a[x] = y;
        } else {
            for(int j=0; j<n; j++){
                ll z = max(a[j], y);
                ans += z - s[j][x];
                s[j][x] = z;
            }
            b[x] = y;
        }

        allans.push_back(ans);
    }
}


void solve(){
    vector<pair<ll, int>> ps, qs;
    for(int i=0; i<q; i++){
        if(ts[i]==1) ps.push_back({ys[i], i});
        else qs.push_back({ys[i], i});
    }
    
    sort(ps.begin(), ps.end());
    sort(qs.begin(), qs.end());

    vector<pair<ll, int>> a(n), b(m);

    SegmentTree<pair<ll, int>> sa(ps.size()+1, {0, 0}), sb(qs.size()+1, {0, 0});

    ll ans = 0;
    for(int i=0; i<q; i++){
        ll r, s;
        if(ts[i]==1){
            int lb = lower_bound(qs.begin(), qs.end(), pair<ll, int>{a[xs[i]].first, 0}) - qs.begin();
            auto ql = sb.query(lb, qs.size()+1);
            dbg("a", lb, a[xs[i]].first, qs[lb].first, qs[lb].second, ql.first, ql.second, sb.query(0, 1).first);
            r = ql.first + (m-ql.second) * a[xs[i]].first;

            int kb = lower_bound(qs.begin(), qs.end(), pair<ll, int>{ys[i], 0}) - qs.begin();
            auto qk = sb.query(kb, qs.size()+1);
            s = qk.first + (m-qk.second) * ys[i];

            int ka = lower_bound(ps.begin(), ps.end(), pair<ll, int>{ys[i], i}) - ps.begin();
            int la = lower_bound(ps.begin(), ps.end(), a[xs[i]]) - ps.begin();
            if(a[xs[i]].first>0) sa.update(la, {0, 0});
            sa.update(ka, {ys[i], 1});
            a[xs[i]] = {ys[i], i};
        } else {
            int la = lower_bound(ps.begin(), ps.end(), pair<ll, int>{b[xs[i]].first, 0}) - ps.begin();
            auto ql = sa.query(la, ps.size()+1);
            r = ql.first + (n-ql.second) * b[xs[i]].first;

            int ka = lower_bound(ps.begin(), ps.end(), pair<ll, int>{ys[i], 0}) - ps.begin();
            auto qk = sa.query(ka, ps.size()+1);
            s = qk.first + (n-qk.second) * ys[i];

            int kb = lower_bound(qs.begin(), qs.end(), pair<ll, int>{ys[i], i}) - qs.begin();
            int lb = lower_bound(qs.begin(), qs.end(), b[xs[i]]) - qs.begin();
            if(b[xs[i]].first>0) sb.update(lb, {0, 0});
            sb.update(kb, {ys[i], 1});
            b[xs[i]] = {ys[i], i};
        }
        dbg(i, r, s);
        ans += s - r;
        allans.push_back(ans);
    }
}