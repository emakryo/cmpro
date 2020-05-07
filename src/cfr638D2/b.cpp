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
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int i=0; i<n; i++) cin >> a[i];

	set<int> uniq;
	for(int i=0; i<n; i++) uniq.insert(a[i]);

	if(uniq.size()>k){
		cout << -1 << endl;
		return;
	}

	vector<int> ans;
	for(int i=0; i<n; i++){
		for(int x: uniq) ans.push_back(x);
		for(int j=0; j<k-uniq.size(); j++) ans.push_back(1);
	}

	cout << ans.size() << endl;
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
