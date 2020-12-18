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

    int n, m, k;
    cin >> n >> m >> k;

    vector<map<int, int>> follows(n);
    vector<vector<int>> tweets(n);
    vector<int> count(n);

    for(int i=0; i<m; i++){
        char q; cin >> q;
        if(q=='t'){
            int j; cin >> j;
            j--;
            tweets[j].push_back(i);
        } else if(q=='f'){
            int j, k; cin >> j >> k;
            j--; k--;
            follows[j][k] = i;
            follows[k][j] = i;
        } else {
            int j, k; cin >> j >> k;
            j--; k--;
            count[j] += tweets[k].end() - lower_bound(tweets[k].begin(), tweets[k].end(), follows[j][k]);
            count[k] += tweets[j].end() - lower_bound(tweets[j].begin(), tweets[j].end(), follows[j][k]);
            follows[j].erase(k);
            follows[k].erase(j);
        }
    }

    for(int i=0; i<n; i++){
        count[i] += tweets[i].size();

        for(auto p: follows[i]){
            int j = p.first;
            int t = p.second;
            count[i] += tweets[j].end() - lower_bound(tweets[j].begin(), tweets[j].end(), t);
        }
    }

    sort(count.rbegin(), count.rend());
    dbg(count);
    cout << count[k-1] << endl;
    return 0;
}