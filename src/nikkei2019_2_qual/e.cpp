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
	ll k;
	cin >> n >> k;

	if(2*k-1>n) {
		cout << -1 << endl;
		return 0;
	}

	vector<tuple<ll, ll, ll>> v;
	for(int i=0; i<k-1; i++){
		v.push_back({k+2*n+1+2*i, n+1+i, k+n+i});
		dbg(k+2*n+1+2*i, n+1+i, k+n+i);
	}
	for(int i=0; i<n-k+1; i++){
		v.push_back({3*k+n-1+2*i, k+i, 2*k+n-1+i});
		dbg(3*k+n-1+2*i, k+i, 2*k+n-1+i);
	}
	sort(v.begin(), v.end());
	for(int i=0; i<n; i++){
		cout << get<1>(v[i]) << " " << get<2>(v[i]) << " " << k+2*n+i << endl;
	}
	return 0;
}
