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

struct Passport {
    string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;

    void clear() {
        byr.clear();
        iyr.clear();
        eyr.clear();
        hgt.clear();
        hcl.clear();
        ecl.clear();
        pid.clear();
        cid.clear();
    }

    bool valid() {
        if(byr.size()!=4) return false;
        stringstream ss(byr);
        int n; ss >> n;
        dbg("byr", byr, n);
        if(n<1920||2002<n) return false;
        if(iyr.size()!=4) return false;
        ss = stringstream(iyr);
        ss >> n;
        dbg("iyr", iyr, n);
        if(n<2010||2020<n) return false;
        ss = stringstream(eyr);
        ss >> n;
        dbg("eyr", n);
        if(n<2020||2030<n) return false;
        ss = stringstream(hgt);
        ss >> n;
        string u;
        ss >> u;
        if(u=="cm"){
            if(n<150||193<n) return false;
        } else if(u=="in"){
            if(n<59||76<n) return false;
        } else {
            return false;
        }

        if(hcl[0]!='#') return false;
        for(auto c: hcl.substr(1)){
            if(!(('0'<=c&&c<='9')||('a'<=c&&c<='f'))) return false;
        }
        if(ecl!="amb"&&ecl!="blu"&&ecl!="brn"&&ecl!="gry"&&ecl!="grn"&&ecl!="hzl"&&ecl!="oth"){
            return false;
        }

        if(pid.size()!=9) return false;
        for(auto c: pid){
            if(c<'0'||'9'<c) return false;
        }

        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    string buf;
    Passport p;
    vector<Passport> ps;

    while(getline(cin, buf)){
        if(buf == ""){
            ps.push_back(p);
            p.clear();
            continue;
        }
        stringstream ss(buf);
        string kv;
        while(ss >> kv){
            int d = kv.find(':');
            string key = kv.substr(0, d);
            string val = kv.substr(d+1);
            if(key=="byr") p.byr = val;
            else if(key=="iyr") p.iyr = val;
            else if(key=="eyr") p.eyr = val;
            else if(key=="hgt") p.hgt = val;
            else if(key=="hcl") p.hcl = val;
            else if(key=="ecl") p.ecl = val;
            else if(key=="pid") p.pid = val;
            else if(key=="cid") p.cid = val;
            else {
                cerr << "Invalid key" << endl;
                return 0;
            }
        }
    }
    ps.push_back(p);

    dbg(ps.size());

    int ans = 0;
    for(auto p: ps) {
        if(p.valid()){
            ans++;
            dbg("valid");
        }
    }

    cout << ans << endl;

    return 0;
}