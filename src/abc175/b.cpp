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
	vector<int> l(n); cin >> l;
	sort(l.begin(), l.end());

	int ans = 0;

	for(int i=0; i<n; i++) for(int j=i+1; j<n; j++) for(int k=j+1; k<n; k++) {
		if(l[i]==l[j]) continue;
		if(l[j]==l[k]) continue;

		if(l[i]+l[j]>l[k]) ans++;
	}

	cout << ans << endl;
	return 0;
}
