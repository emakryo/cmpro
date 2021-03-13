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

    string s;
    cin >> s;

    ll ans = 0;
    int last_seq_char = -1;
    int last_seq_index = s.size();
    vector<int> count(26, 0);
    for(int i=s.size()-3; i>=0; i--){
        int c = s[i]-'a';
        if(s[i]==s[i+1]){
            ll add = 0;
            if(s[i+1]!=s[i+2]){
                if(c == last_seq_char){
                    add = last_seq_index - i - count[c] - 2;
                } else {
                    add = s.size() - i - count[c] - 2;
                }
                dbg(i, (char)(c+'a'), add, (char)(last_seq_char+'a'), last_seq_index, count[c]);
            }
            last_seq_index = i;
            last_seq_char = c;

            for(int j=0; j<26; j++) count[j] = 0;
            count[c] = -2;
            ans += add;
        } else {
            dbg(i, s[i+2]);
            count[s[i+2]-'a']++;
        }
    }

    cout << ans << endl;
    return 0;
}