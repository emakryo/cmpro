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

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

void solve(){
	ll n; cin >> n;
	ll k = 1;
	vector<int> ans;
	while(n>3*k){
		dbg(n, k);
		n -= k;
		if(n>4*k){
			ans.push_back(k);
			k*=2;
		} else {
			ans.push_back(n/2-k);
			k+=n/2-k;
		}

	}
	dbg(n, k);
	n-=k;
	ans.push_back(n-k);
	k+=n-k;
	dbg(n, k);

	cout << ans.size() << endl;
	cout << ans << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	int t; cin>>t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
