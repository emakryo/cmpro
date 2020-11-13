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
    
    int n, x, y; cin >> n >> x >> y;
    int offset = 210;

    vector<vector<bool>> b(430, vector<bool>(430));
    for(int i=0; i<n; i++){
        int xi, yi;
        cin >> xi >> yi;
        b[xi+offset][yi+offset] = true;
    }

    vector<vector<int>> d(430, vector<int>(430, 1e9));
    d[offset][offset] = 0;

    queue<pair<int, pair<int, int>>> que;
    que.push({0, {offset, offset}});

    while(que.size()){
        int m = que.front().first;
        int xi = que.front().second.first;
        int yi = que.front().second.second;
        que.pop();

        int dx[] = {1, 0, -1, 1, -1, 0};
        int dy[] = {1, 1, 1, 0, 0, -1};

        for(int k=0; k<6; k++){
            int xj = xi+dx[k];
            int yj = yi+dy[k];

            if(xj<0||430<=xj||yj<0||430<=yj||b[xj][yj]||d[xj][yj]<1e9) continue;
            d[xj][yj] = m+1;
            que.push({m+1, {xj, yj}});
        }
    }

    if(d[x+offset][y+offset]<1e9){
        cout << d[x+offset][y+offset] << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}