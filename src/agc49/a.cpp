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
    int n;
    cin >> n;
    vector<string> s(n);
    cin >> s;

    double ans = 0;
    for(int i=0; i<n; i++){
        vector<bool> visit(n);
        queue<int> que;
        visit[i] = true;
        que.push(i);
        while(que.size()) {
            int j = que.front();
            que.pop();
            for(int k=0; k<n; k++){
                if(s[k][j]=='1'&&!visit[k]){
                    visit[k] = true;
                    que.push(k);
                }
            }
        }

        int m = 0;
        for(int j=0; j<n; j++){
            if(visit[j]) m++;
        }

        ans += 1.0 / m;
    }

    cout << ans << endl;
    return 0;
}