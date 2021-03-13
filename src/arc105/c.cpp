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

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n, m; cin >> n >> m;
    vector<ll> w(n);
    cin >> w;
    vector<ll> l(m), v(m);
    for(int i=0; i<m; i++) cin >> l[i] >> v[i];

    sort(w.begin(), w.end());

    if(*max_element(w.begin(), w.end()) > *min_element(v.begin(), v.end())){
        cout << -1 << endl;
        return 0;
    }

    map<ll, ll> lb;
    for(int i=0; i<m; i++){
        lb[v[i]] = max(lb[v[i]], l[i]);
    }

    ll lmax = 0;
    for(auto &p: lb){
        if(p.second < lmax) {
            p.second = lmax;
        } else {
            lmax = p.second;
        }
        dbg(p.first, p.second);
    }

    ll ans = 1e18;
    do {
        dbg(w);
        vector<ll> dist(n);
        for(int i=0; i<n; i++){
            ll s = 0;
            for(int j=i; j<n; j++){
                s += w[j];
                auto it = lb.lower_bound(s);
                if(it == lb.begin()){
                        dbg(i, j, s, 0);
                        dist[j] = max(dist[j], dist[i]);
                } else {
                    ll d = (--it)->second;
                    dbg(i, j, s, d);
                    dist[j] = max(dist[j], dist[i] + d);
                }
            }
        }
        dbg(dist);
        ans = min(ans, dist[n-1]);
    // } while(false);

    } while(next_permutation(w.begin(), w.end()));

    cout << ans << endl;
    return 0;
}