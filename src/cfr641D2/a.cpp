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
	int p=n;
	for(int i=2; i*i<=n; i++){
		if(n%i==0){
			p=i;
			break;
		}
	}
	if(p==2){
		cout << n+2*k << endl;
	} else {
		cout << n+p+2*(k-1) << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int t = 0; cin >> t;
	for(int i=0; i<t; i++) solve();

	return 0;
}
