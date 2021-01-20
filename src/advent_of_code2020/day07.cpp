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

    string buf;
    regex re_sub(R"(([a-zA-Z ]+) bags contain )");
    regex re_obj(R"((\d+) ([a-zA-Z ]+) bags?(?:, |\.))");
    smatch matches;
    map<string, map<string, int>> rules;
    map<string, vector<string>> parents;
    while (getline(cin, buf)) {
        string x;
        if(regex_search(buf, matches, re_sub) && matches[1].matched) {
            x = matches[1].str();
            buf = buf.substr(matches[0].length());
        } else {
            cerr<<"Invalid"<<endl;
            return 1;
        }
        dbg(x);
        while(regex_search(buf, matches, re_obj)) {
            stringstream ss(matches[1].str());
            int n;
            ss >> n;
            string y = matches[2].str();

            rules[x][y] = n;
            parents[y].push_back(x);
            dbg(n, y);
            buf = buf.substr(matches[0].length());
        }
    }

    ll ans = -1;
    queue<pair<ll, string>> que;
    que.push({1, "shiny gold"});

    while(que.size()){
        auto x = que.front();
        que.pop();
        ans += x.first;

        for(auto y: rules[x.second]){
            que.push({x.first * y.second, y.first});
        }
    }

    cout << ans << endl;

    return 0;
}