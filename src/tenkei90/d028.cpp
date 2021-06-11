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
    vector<vector<int>> s(1001, vector<int>(1001));
    for(int i=0; i<n; i++){
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;

        s[lx][ly]++;
        s[lx][ry]--;
        s[rx][ly]--;
        s[rx][ry]++;
    }

    for(int i=0; i<1001; i++) for(int j=0; j<1001; j++){
        if(i>0){
            if(j>0) s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
            else s[i][j] += s[i-1][j];
        } else {
            s[i][j] += s[i][j-1];
        }
    }

    vector<int> ans(n+1);
    for(int i=0; i<1001; i++) for(int j=0; j<1001; j++){
        ans[s[i][j]]++;
    }

    for(int i=1; i<n+1; i++){
        cout << ans[i] << endl;
    }
    return 0;
}