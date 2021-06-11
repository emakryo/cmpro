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

    int h, w;
    cin >> h >> w;
    int rs, cs, rt, ct;
    cin >> rs >> cs >> rt >> ct;
    rs--; cs--;
    rt--; ct--;
    vector<string> s(h);
    cin >> s;

    vector<int> dist(h*w*4, 1e9);
    deque<pair<int, int>> q;
    for(int k=0; k<4; k++){
        int v = 4*h*cs+4*rs+k;
        q.push_front({v, 0});
        dist[v] = 0;
    }

    while(q.size()){
        int v = q.front().first;
        int d = q.front().second;
        q.pop_front();
        if(dist[v]<d) continue;
        dbg(v/4%h, v/4/h, v%4);

        int dx[] = {0, -1, 0, 1};
        int dy[] = {-1, 0, 1, 0};

        for(int k=0; k<4; k++){
            int x = v/4%h + dx[k];
            int y = v/4/h + dy[k];
            if(x<0||h<=x||y<0||w<=y||s[x][y]=='#') continue;
            int u = 4*h*y+4*x+k;
            if(v%4==k){
                if(dist[v]<dist[u]){
                    dist[u] = dist[v];
                    q.push_front({u, dist[u]});
                }
            } else {
                if(dist[v]+1<dist[u]){
                    dist[u] = dist[v]+1;
                    q.push_back({u, dist[u]});
                }
            }
        }
    }

    int ans = 1e9;
    for(int k=0; k<4; k++){
        ans = min(ans, dist[4*h*ct+4*rt+k]);
    }

    cout << ans << endl;
    return 0;
}