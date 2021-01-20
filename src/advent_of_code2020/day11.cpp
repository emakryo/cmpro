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

    vector<string> s;
    string buf;
    while(cin >> buf){
        s.push_back(buf);
    }

    vector<string> next(s);
    int w = s[0].size();
    int h = s.size();
    dbg(h, w);

    vector<vector<vector<pair<int, int>>>> adj(
        h,
        vector<vector<pair<int, int>>>(w)
    );

    for(int i=0; i<h; i++){
        pair<int, int> last = {-1, -1};
        for(int j=0; j<w; j++){
            if(s[i][j]=='.') continue;
            adj[i][j].push_back(last);
            last = {i, j};
        }

        last = {-1, -1};
        for(int j=w-1; j>=0; j--){
            if(s[i][j]=='.') continue;
            adj[i][j].push_back(last);
            last = {i, j};
        }
    }

    for(int j=0; j<w; j++){
        int last = -1;
        for(int i=0; i<h; i++){
            if(s[i][j]=='.') continue;
            adj[i][j].push_back({last, j});
            last = i;
        }

        last = -1;
        for(int i=h-1; i>=0; i--){
            if(s[i][j]=='.') continue;
            adj[i][j].push_back({last, j});
            last = i;
        }
    }

    for(int i=-w+1; i<h; i++){
        pair<int, int> last = {-1, -1};
        int x0 = max(0, i);
        int y0 = max(0, -i);
        for(int k=0; k<min(i+w, h-x0); k++){
            if(s[x0+k][y0+k]=='.') continue;
            adj[x0+k][y0+k].push_back(last);
            last = {x0+k, y0+k};
        }

        last = {-1, -1};
        for(int k=min(i+w, h-x0)-1; k>=0; k--){
            if(s[x0+k][y0+k]=='.') continue;
            adj[x0+k][y0+k].push_back(last);
            last = {x0+k, y0+k};
        }
    }

    for(int i=0; i<h+w-1; i++){
        pair<int, int> last = {-1, -1};
        int x0 = i;
        int y0 = 0;
        for(int k=max(0, i-h+1); k<min(w, i+1); k++){
            dbg(i, x0-k, k);
            if(s[x0-k][k]=='.') continue;
            adj[x0-k][k].push_back(last);
            last = {x0-k, k};
        }
        last = {-1, -1};
        for(int k=min(w, i+1)-1; k>=max(0, i-h+1); k--){
            if(s[x0-k][k]=='.') continue;
            adj[x0-k][k].push_back(last);
            last = {x0-k, k};
        }
    }

    while(true){
        bool changed = false;

        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(s[i][j]=='.') continue;
                int a = 0;
                for(int k=0; k<8; k++){
                    int nx = adj[i][j][k].first;
                    int ny = adj[i][j][k].second;
                    if(0<=nx&&nx<h&&0<=ny&&ny<w&&s[nx][ny]=='#') a++;
                }
                if(s[i][j]=='L'&&a==0){
                    next[i][j] = '#';
                    changed = true;
                } else if(s[i][j]=='#'&&a>=5){
                    next[i][j] = 'L';
                    changed = true;
                } else {
                    next[i][j] = s[i][j];
                }
            }
        }

        swap(s, next);

        if(!changed) break;
    }

    int ans = 0;
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(s[i][j]=='#') ans++;
        }
    }
    cout << ans << endl;
    return 0;
}