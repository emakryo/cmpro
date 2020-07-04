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

bool match(char x, char y){
	return x=='?'||y=='?'||x==y;
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	string a, b, c;
	cin >> a >> b >> c;

	int z = 2005;
	vector<bool> ab(2*z, true), bc(2*z, true), ca(2*z, true);

	for(int i=0; i<a.size(); i++) for(int j=0; j<b.size(); j++) {
		if(!match(a[i], b[j])) ab[i-j+z] = false;
	}
	for(int i=0; i<b.size(); i++) for(int j=0; j<c.size(); j++) {
		if(!match(b[i], c[j])) bc[i-j+z] = false;
	}
	for(int i=0; i<c.size(); i++) for(int j=0; j<a.size(); j++) {
		if(!match(c[i], a[j])) ca[i-j+z] = false;
	}

	int ans = 1e9;
	for(int i=-2*z; i<2*z; i++) for(int j=-2*z; j<2*z; j++){
		int p = i+z;
		int q = j-i+z;
		int r = -j+z;
		if(0<=p&&p<2*z&&!ab[p]) continue;
		if(0<=q&&q<2*z&&!bc[q]) continue;
		if(0<=r&&r<2*z&&!ca[r]) continue;
		int s = max({(int)a.size(), (int)b.size()+i, (int)c.size()+j});
		int t = min({0, i, j});
		dbg(i, j, p, q, r, s, t, s-t);
		ans = min(ans, s-t);
	}

	cout << ans << endl;

	return 0;
}
