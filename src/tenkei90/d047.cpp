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

// from https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
#include<bits/stdc++.h>

// Z array: Z[i] = maximum n s.t. str[0..n] == str[i..i+n]
template<typename T>
std::vector<int> get_z_array(T &str) {
    int n = str.size();
    std::vector<int> Z(n);
    int L, R, k;
    // [L,R] make a window which matches with prefix of s
    L = R = 0;
    for (int i=1; i<n; i++) {
        // if i>R nothing matches so we will calculate.
        // Z[i] using naive way.
        if (i > R) {
            L = R = i;
            // R-L = 0 in starting, so it will start
            // checking from 0'th index. For example,
            // for "ababab" and i = 1, the value of R
            // remains 0 and Z[i] becomes 0. For string
            // "aaaaaa" and i = 1, Z[i] and R become 5
            while (R<n && str[R-L] == str[R]) R++;
            Z[i] = R-L;
            R--;
        } else {
            // k = i-L so k corresponds to number which
            // matches in [L,R] interval.
            k = i-L;
            // if Z[k] is less than remaining interval
            // then Z[i] will be equal to Z[k].
            // For example, str = "ababab", i = 3, R = 5
            // and L = 2
            if (Z[k] < R-i+1) Z[i] = Z[k];
            // For example str = "aaaaaa" and i = 2, R is 5,
            // L is 0
            else {
                // else start from R and check manually
                L = i;
                while (R<n && str[R-L] == str[R]) R++;
                Z[i] = R-L;
                R--;
            }
        }
    }
    return Z;
}

std::vector<int> occurance(std::string &text, std::string &pattern){
    std::string concat = pattern + "$" + text;
    int np = pattern.size();
    std::vector<int> z = get_z_array(concat);
    std::vector<int> idx;

    for(int i=0; i<concat.size()-np-1; i++){
        if(z[i+np+1] >= np) idx.push_back(i);
    }
    return idx;
}


int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    int ans = 0;
    vector<int> xs(2*n+1);
    for(int i=0; i<n; i++){
        if(s[i]=='R') xs[i] = 0;
        if(s[i]=='G') xs[i] = 1;
        if(s[i]=='B') xs[i] = 2;
    }
    xs[n] = -1;

    for(int i=0; i<n; i++){
        if(t[i]=='R') xs[i+n+1] = 0;
        if(t[i]=='G') xs[i+n+1] = 2;
        if(t[i]=='B') xs[i+n+1] = 1;
    }
    vector<int> z = get_z_array(xs);
    for(int i=0; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("s", "r", ans);

    for(int i=0; i<n; i++){
        if(t[i]=='R') xs[i+n+1] = 2;
        if(t[i]=='G') xs[i+n+1] = 1;
        if(t[i]=='B') xs[i+n+1] = 0;
    }
    z = get_z_array(xs);
    for(int i=0; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("s", "g", ans);

    for(int i=0; i<n; i++){
        if(t[i]=='R') xs[i+n+1] = 1;
        if(t[i]=='G') xs[i+n+1] = 0;
        if(t[i]=='B') xs[i+n+1] = 2;
    }
    z = get_z_array(xs);
    for(int i=0; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("s", "b", ans);

    for(int i=0; i<n; i++){
        if(t[i]=='R') xs[i] = 0;
        if(t[i]=='G') xs[i] = 1;
        if(t[i]=='B') xs[i] = 2;
    }

    for(int i=0; i<n; i++){
        if(s[i]=='R') xs[i+n+1] = 0;
        if(s[i]=='G') xs[i+n+1] = 2;
        if(s[i]=='B') xs[i+n+1] = 1;
    }
    z = get_z_array(xs);
    for(int i=1; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("t", "r", ans);

    for(int i=0; i<n; i++){
        if(s[i]=='R') xs[i+n+1] = 2;
        if(s[i]=='G') xs[i+n+1] = 1;
        if(s[i]=='B') xs[i+n+1] = 0;
    }
    z = get_z_array(xs);
    for(int i=1; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("t", "g", ans);

    for(int i=0; i<n; i++){
        if(s[i]=='R') xs[i+n+1] = 1;
        if(s[i]=='G') xs[i+n+1] = 0;
        if(s[i]=='B') xs[i+n+1] = 2;
    }
    z = get_z_array(xs);
    for(int i=1; i<n; i++){
        if(z[i+n+1]==n-i) ans++;
    }
    dbg("t", "b", ans);

    cout << ans << endl;

    return 0;
}