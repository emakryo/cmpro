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

int score(vector<int> &x, vector<int> &used){
    ll used_sum = 0, x_sum = 0;
    for(auto a: x) x_sum += a;
    for(auto a: used) used_sum += a;
    
    ll prd = 1;
    for(auto a: used){
        prd *= a;
        if(prd > x_sum-used_sum) return 0;
    }
    if(x_sum-used_sum==prd) return prd;
    else return 0;
}

int dfs(int k, vector<int> &x, vector<int> &used){
    if(k>=x.size()) return 0;
    int ans = dfs(k+1, x, used);

    used.push_back(x[k]);
    ll prd = 1;
    int sum = 0;
    for(auto a: x) sum += a;
    for(auto a: used){
        prd *= a;
        if(prd>sum){
            used.pop_back();
            return 0;
        }
    }
    if(prd<=sum){
        dbg(prd, sum, used);
        ans = max(ans, score(x, used));
        ans = max(dfs(k+1, x, used), ans);
    }
    used.pop_back();

    return ans;
}

void solve1(){
    int m; cin >> m;
    vector<int> x;
    for(int i=0; i<m; i++){
        int p, n;
        cin >> p >> n;
        for(int i=0; i<n; i++) x.push_back(p);
    }
    vector<int> used;
    cout << dfs(0, x, used) << endl;
}

void solve(){
    int m; cin >> m;
    map<int, ll> x;
    for(int i=0; i<m; i++){
        int p;
        ll n;
        cin >> p >> n;
        x[p] = n;
    }

    ll sum = 0;
    for(auto pa: x){
        sum += pa.first * pa.second;
    }

    ll ans = 0;
    for(ll c = max(2ll, sum - 29940); c <= sum; c++){
        map<int, ll> y;
        bool ok = true;
        ll sum2 = 0;
        ll t = c;
        for(auto pa: x){
            while(t%pa.first==0){
                y[pa.first]++;
                t /= pa.first;
                sum2 += pa.first;
            }
            if (y[pa.first]>pa.second) ok =false;
        }
        if(t != 1) ok = false;

        if(ok && sum-sum2==c){
            ans = max(ans, c);
        }
    }

    cout << ans << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}