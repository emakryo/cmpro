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

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    sort(a.begin(), a.end());
    vector<pair<int, int>> b;
    int i = 0;
    while(i < n) {
        int l = upper_bound(a.begin(), a.end(), a[i])-a.begin();
        b.push_back({a[i], l-i});
        i = l;
    }

    const int INF = 1e9;
    int m = b.size();
    int l = 32;
    vector<vector<int>> dp(m+1, vector<int>(l, INF));
    dp[0][0] = 0;

    for(int i=0; i<m; i++){
        int h = upper_bound(b.begin(), b.end(), pair<int,int>{b[i].first/2, INF}) - b.begin();

        for(int j=0; j<l; j++){
            dp[i+1][j] = dp[i][j] + b[i].second;
            if(j>0){
                dp[i+1][j] = min(dp[i+1][j], dp[h][j-1]);
            }
        }
    }

    int ans;
    for(int i=0; i<l; i++){
        if(dp[m][i]<=k){
            ans = i;
            break;
        }
    }
    cout << ans << " " << dp[m][ans] << endl;
    return 0;
}