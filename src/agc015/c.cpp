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

#include<bits/stdc++.h>

template <typename T>
struct SegmentTree{
    std::vector<T> v;
    T def;
    int n;
    SegmentTree(int n_, T default_value): def(default_value){
        n = 1;
        while(n<n_) n <<= 1;
        v.assign(2*n-1, def);
    }
    template<class I>
    SegmentTree(I first, I last, T default_value): SegmentTree(last-first, default_value){
        copy(first, last, v.begin()+n-1);
        for(int i=n-2; i>=0; i--)
            v[i] = merge(v[2*i+1], v[2*i+2]);
    }
    SegmentTree(std::vector<T> initial_data, T default_value):
    SegmentTree(initial_data.begin(), initial_data.end(), default_value){}
    // 0 <= idx < n
    void update(int idx, T val){
        idx += n-1;
        v[idx] = val;
        while(idx > 0){
            idx = (idx-1)/2;
            v[idx] = merge(v[2*idx+1], v[2*idx+2]);
        }
    }
    T q(int a, int b, int k, int l, int r){
        if(a<=l&&r<=b) return v[k];
        if(b<=l||r<=a) return def;
        return merge(q(a, b, 2*k+1, l, (l+r)/2), q(a, b, 2*k+2, (l+r)/2, r));
    }
    // 0 <= a < b < n
    T query(int a, int b){
        return q(a, b, 0, 0, n);
    }
    T merge(T left, T right);
};

// Example

template <typename T>
T SegmentTree<T>::merge(T a, T b){
    return a+b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m, q;
    cin >> n >> m >> q;
    vector<string> s(n);
    cin >> s;

    vector<vector<int>> rt(n+1, vector<int>(m+1));
    vector<vector<bool>> done(n, vector<bool>(m));
    vector<SegmentTree<int>> up(n+1, SegmentTree(m+1, 0));
    vector<SegmentTree<int>> down(n+1, SegmentTree(m+1, 0));
    vector<SegmentTree<int>> left(m+1, SegmentTree(n+1, 0));
    vector<SegmentTree<int>> right(m+1, SegmentTree(n+1, 0));

    queue<pair<int, int>> que;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(done[i][j]||s[i][j]=='0') continue;
            dbg(i, j);
            done[i][j] = true;
            rt[i+1][j+1] = 1;
            que.push({i, j});
            while(que.size()){
                auto p = que.front();
                que.pop();
                for(int k=0; k<4; k++){
                    int dx[] = {0, -1, 0, 1};
                    int dy[] = {-1, 0, 1, 0};
                    int x = p.first+dx[k];
                    int y = p.second+dy[k];
                    if(x<0||n<=x||y<0||m<=y){
                        continue;
                    }
                    if(done[x][y]||s[x][y]=='0') continue;
                    que.push({x, y});
                    done[x][y] = true;

                    int px = p.first;
                    int py = p.second;
                    if(k==0){
                        left[py].update(px, 1);
                    } else if(k==1){
                        up[px].update(py, 1);
                    } else if(k==2){
                        right[py].update(px, 1);
                    } else {
                        down[px].update(py, 1);
                    }
                }
            }

        }
    }

    for(int i=0; i<n; i++) for(int j=0; j<m; j++){
        rt[i+1][j+1] += rt[i+1][j] + rt[i][j+1] - rt[i][j];
    }

    for(int i=0; i<q; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int t = rt[x2][y2] - rt[x2][y1-1] - rt[x1-1][y2] + rt[x1-1][y1-1];
        int u = up[x2].query(y1-1, y2);
        int d = x1>=2 ? down[x1-2].query(y1-1, y2) : 0;
        int r = y1>=2 ? right[y1-2].query(x1-1, x2) : 0;
        int l = left[y2].query(x1-1, x2);
        dbg(t, u, d, r, l);
        cout << t + u + d +r + l << endl;
    }
    
    return 0;
}