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
    vector<int> k(n);
    vector<deque<int>> t(n);
    for(int i=0; i<n; i++){
        cin >> k[i];
        for(int j=0; j<k[i]; j++){
            int tt; cin >> tt;
            t[i].push_back(tt);
        }
    }
    int m; cin >> m;
    vector<int> a(m); cin >> a;

    map<int, int> x1, x2;
    for(int i=0; i<n; i++){
        if(t[i].size()){
            x1[t[i][0]] = i;
        }
        if(t[i].size()>1){
            x2[t[i][1]] = i;
        }
    }

    for(int i=0; i<m; i++){
        auto z1 = x1.rbegin();
        auto z2 = x2.rbegin();
        if(a[i]==1 || z2 == x2.rend() || z1->first > z2->first){
            int j = z1->second;
            int x = z1->first;
            x1.erase(x);
            t[j].pop_front();
            if(t[j].size()){
                x2.erase(t[j][0]);
                x1[t[j][0]] = j;

                if(t[j].size()>1){
                    x2[t[j][1]] = j;
                }
            }
            cout << x << "\n";
        } else {
            int j = z2->second;
            int x = z2->first;
            x2.erase(x);
            int tt = t[j][0];
            t[j].pop_front();
            t[j].pop_front();
            t[j].push_front(tt);
            if(t[j].size()>1){
                x2[t[j][1]] = j;
            }
            cout << x << "\n";
        }
    }

    return 0;
}