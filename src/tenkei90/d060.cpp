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

ostream& operator<<(ostream &os, pair<int, int> &x){
    return cout << x.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> dp(n+1, 1e9);
    vector<int> lis(n);
    dp[0] = 0;
    lis[0] = 1;

    for(int i=0; i<n; i++){
        int k = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        dp[k] = a[i];
        lis[i] = k;
    }

    reverse(a.begin(), a.end());
    dp.assign(n+1, 1e9);
    vector<int> rlis(n);
    dp[0] = 0;
    rlis[0] = 1;
    
    for(int i=0; i<n; i++){
        int k = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        dp[k] = a[i];
        rlis[i] = k;
    }

    dbg(lis);
    dbg(rlis);

    int ans = 0;
    for(int i=0; i<n; i++){
        ans = max(ans, lis[i]+rlis[n-1-i]-1);
    }
    cout << ans << endl;

    return 0;
}