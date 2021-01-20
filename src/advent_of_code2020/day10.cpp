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
    vector<int> js(1, 0);
    int x;
    while(cin>>x){
        js.push_back(x);
    }

    sort(js.begin(), js.end());
    dbg(js);
    /*
    int d1=0, d3=1;
    if(js[0]==1) d1++;
    if(js[0]==3) d3++;
    for(int i=0; i<js.size()-1; i++){
        if(js[i+1]-js[i]==1) d1++;
        else if(js[i+1]-js[i]==3) d3++;
    }
    dbg(d1, d3);
    cout << (ll)d1*d3 << endl;
    */

   vector<ll> dp(js.size());
   dp[0] = 1;
   for(int i=1; i<js.size(); i++){
       for(int k=1; k<4; k++){
           if(i-k>=0&&js[i]-js[i-k]<=3){
               dp[i] += dp[i-k];
           }
       }
   }

    cout << dp[js.size()-1] << endl;

    return 0;
}