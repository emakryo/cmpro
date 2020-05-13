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
	int n; cin >> n;
	ll k; cin >> k;
	vector<ll> a(n);
	for(int i=0; i<n; i++) cin >> a[i];

	bool exist = false;
	bool ok = false;
	for(int i=0; i<n; i++){
		if(a[i]==k) exist = true;
		if(i<n-1){
			if(a[i]>=k&&a[i+1]>=k){
				ok = true;
			}
		}
		if(i<n-2){
			vector<ll> x{a[i], a[i+1], a[i+2]};
			sort(x.begin(), x.end());
			if(x[1]>=k) ok = true;
		}
	}

	if(exist&&ok||exist&&a.size()==1){
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}



int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
