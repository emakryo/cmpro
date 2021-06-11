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

vector<vector<int>> memo;

int grundy(int w, int b){
    if(w==0&&b<=1) return 0;
    if(memo[w][b]>=0){
        return memo[w][b];
    }

    set<int> t;
    if(w>0) t.insert(grundy(w-1, b+w));

    for(int k=1; k<=b/2; k++){
        t.insert(grundy(w, b-k));
    }

    int x = 0;
    while(t.count(x)){
        x++;
    }
    memo[w][b] = x;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<int> ws(n), bs(n);
    cin >> ws >> bs;

    memo = vector<vector<int>>(51, vector<int>(1400, -1));

    int x = 0;
    for(int i=0; i<n; i++){
        x ^= grundy(ws[i], bs[i]);
    }

    cout << (x==0?"Second":"First") << endl;

    return 0;
}