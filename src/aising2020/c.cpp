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

	vector<int> ans(n+1);
	for(int x=1; x<100; x++){
		for(int y=1; y<100; y++){
			for(int z=1; z<100; z++){
				int k = x*x+y*y+z*z+x*y+y*z+z*x;
				if(k<=n) ans[k]++;
			}
		}
	}

	for(int i=1; i<=n; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
