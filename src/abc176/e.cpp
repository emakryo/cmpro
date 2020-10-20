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
    int h, w, m;
    cin >> h >> w >> m;
    vector<int> hs(m), ws(m);
    for(int i=0; i<m; i++) cin >> hs[i] >> ws[i];

    vector<pair<int, int>> nh(h+1), nw(w+1);
    for(int i=0; i<=h; i++) nh[i].second = i;
    for(int i=0; i<=w; i++) nw[i].second = i;
    for(int i=0; i<m; i++) nh[hs[i]].first++;
    for(int i=0; i<m; i++) nw[ws[i]].first++;

    sort(nh.rbegin(), nh.rend());
    sort(nw.rbegin(), nw.rend());

    set<int> hm, wm;
    for(int i=0; i<=h; i++){
        if(nh[i].first != nh[0].first) break;
        hm.insert(nh[i].second);
        dbg("h", nh[i].second);
    }
    for(int i=0; i<=w; i++){
        if(nw[i].first != nw[0].first) break;
        wm.insert(nw[i].second);
        dbg("w", nw[i].second);
    }

    int cnt = 0;
    for(int i=0; i<m; i++){
        if(hm.count(hs[i])>0 && wm.count(ws[i])>0){
            cnt++;
        }
    }
    dbg(hm.size(), wm.size(), cnt);
    
    int ans = nh[0].first + nw[0].first;
    if(cnt == hm.size() * wm.size()){
        ans--;
    }
    cout << ans << endl;

    return 0;
}