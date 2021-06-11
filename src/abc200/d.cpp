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

    int n; cin >> n;
    vector<ll> a(n);
    cin >> a;

    map<int, vector<int>> dp;
    dp[0] = vector<int>();

    for(int i=0; i<n; i++){
        map<int, vector<int>> next;
        for(int j=0; j<200; j++){
            if(dp.count(j)==0) continue;
            int k = (j+a[i])%200;
            next[k] = vector<int>(dp[j]);
            next[k].push_back(i+1);
        }

        for(int j=0; j<200; j++){
            if(dp.count(j)>0&&dp[j].size()>0&&next.count(j)>0){
                cout << "Yes" << endl;
                dbg(j);
                cout << dp[j].size() << " " << dp[j] << endl;
                cout << next[j].size() << " " << next[j] << endl;
                return 0;
            }

            if(next.count(j)){
                dp[j] = next[j];
            }
        }
    }

    cout << "No" << endl;
    return 0;
}