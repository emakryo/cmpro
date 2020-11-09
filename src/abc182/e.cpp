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

    int h, w, n, m;
    cin >> h >> w >> n >> m;
    vector<string> s1(h, string(w, '.'));
    vector<string> s2(s1);

    for(int i=0; i<n; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        s1[a][b] = 'L';
        s2[a][b] = 'L';
    }

    for(int i=0; i<m; i++){
        int c, d; cin >> c >> d;
        c--; d--;
        s1[c][d] = 'X';
        s2[c][d] = 'X';
    }

    for(int x=0; x<h; x++){
        int left = 0;
        bool bright = false;
        for(int y=0; y<w; y++){
            if(s1[x][y]=='X'){
                bright = false;
                left = y+1;
            }else if(bright){
                s1[x][y] = 'L';
            } else if(s1[x][y]=='L'){
                for(int y0=left; y0<y; y0++) s1[x][y0] = 'L';
                bright = true;
                left = y+1;
            }
        }
    }

    for(int y=0; y<w; y++){
        int left = 0;
        bool bright = false;
        for(int x=0; x<h; x++){
            if(s2[x][y]=='X'){
                bright = false;
                left = x+1;
            }else if(bright){
                s2[x][y] = 'L';
            } else if(s2[x][y]=='L'){
                for(int x0=left; x0<x; x0++) s2[x0][y] = 'L';
                bright = true;
                left = x+1;
            }
        }
    }
    for(int x=0; x<h; x++) dbg(s1[x]);
    for(int x=0; x<h; x++) dbg(s2[x]);

    int ans = 0;
    for(int x=0; x<h; x++) for(int y=0; y<w; y++){
        if(s1[x][y]=='L'||s2[x][y]=='L') ans++;
    }

    cout << ans << endl;

    return 0;
}