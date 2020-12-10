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
    int h, w, n;
    cin >> h >> w >> n;
    vector<int> x(n), y(n);
    for(int i=0; i<n; i++){
        cin >> x[i] >> y[i];
    }

    map<int, vector<int>> ys;
    for(int i=0; i<n; i++){
        ys[x[i]].push_back(y[i]);
    }

    for(auto it=ys.begin(); it!=ys.end(); it++){
        sort(it->second.begin(), it->second.end());
    }

    map<int, int> range;
    range[1] = 2;
    for(int i=2; i<=h; i++){
        for(auto p: range){
            dbg(i, p.first, p.second, ys[i].size());
            if(ys[i].size()==0){
                range[p.first] = p.second+1;
            } else {
                int j = *lower_bound(ys[i].begin(), ys[i].end(), p.first);
                dbg(i, j);
                if(j<p.second){
                    cout << i-1 << endl;
                    return 0;
                }
                if(j>p.second){
                    range[p.first] = p.second+1;
                }
            }
        }
        auto it=range.begin();
        while(it!=range.end()){
            int end = it->second;
            auto jt = it;
            it++;
            if(it->first==end){
                end = it->second;
                range.erase(it->first);
            }
            it = ++jt;
        }
    }

    cout << h << endl;
    return 0;
}