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
    int h, w; cin >> h >> w;
    vector<string> s(h);
    for(int i=0; i<h; i++) cin >>s[i];

    int ans = 0;
    for(int i=0; i<h-1; i++) for(int j=0; j<w-1; j++){
        int dx[] = {0, 1, 0, 1};
        int dy[] = {0, 0, 1, 1};
        int a = 0;
        for(int k=0; k<4; k++){
            if(s[i+dx[k]][j+dy[k]]=='.') a++;
        }
        if(a==1||a==3) ans++;
    }

    cout << ans << endl;
    return 0;
}