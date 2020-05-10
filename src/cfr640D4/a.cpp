
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
	vector<int> ans;
	int d=1;
	while(n>0){
		if(n/d%10>0){
			int x = n/d%10*d;
			ans.push_back(x);
			n-=x;
		}
		d*=10;
	}
	cout << ans.size() << endl;
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin>>t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
