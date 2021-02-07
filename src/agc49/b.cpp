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
    string s, t;
    cin >> s >> t;

    queue<int> si;
    vector<int> ti;
    for(int i=0; i<n; i++){
        if(s[i]=='1') si.push(i);
        if(t[i]=='1') ti.push_back(i);
    }

    ll ans = 0;
    for(int i: ti){
        while(si.size()>1&&si.front()<i){
            int a = si.front();
            si.pop();
            int b = si.front();
            si.pop();
            ans += b-a;
        }
        if(si.size()>0&&si.front()>=i){
            int a = si.front();
            si.pop();
            ans += a-i;
        } else {
            cout << -1 << endl;
            return 0;
        }
    }

    if(si.size()%2){
        cout << -1 << endl;
        return 0;
    }

    while(si.size()>1){
        int a = si.front();
        si.pop();
        int b = si.front();
        si.pop();
        ans += b-a;
    }

    cout << ans << endl;
    return 0;
}