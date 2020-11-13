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

string digits[5] = {
".###..#..###.###.#.#.###.###.###.###.###",
".#.#.##....#...#.#.#.#...#.....#.#.#.#.#",
".#.#..#..###.###.###.###.###...#.###.###",
".#.#..#..#.....#...#...#.#.#...#.#.#...#",
".###.###.###.###...#.###.###...#.###.###",
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<string> s(5); cin >> s;

    string ans;
    for(int i=0; i<n; i++){
        for(int k=0; k<10; k++){
            bool ok = true;
            for(int j=0; j<5; j++){
                if(digits[j].substr(4*k, 4) != s[j].substr(4*i, 4)){
                    ok = false;
                    break;
                }
            }
            if(ok){
                ans += '0'+k;
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}