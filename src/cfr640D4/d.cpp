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
	vector<int> a(n);
	for(int i=0; i<n; i++){
		cin >> a[i];
	}

	int p=0, q=n-1;
	int sum[2] = {0, 0};
	int prev = 0;
	int k = 0;
	while(p<=q){
		int b = 0;
		if(k%2){
			b = a[q--];
			while(q>=p&&b<=prev){
				b += a[q--];
			}
		} else {
			b = a[p++];
			while(p<=q&&b<=prev){
				b+=a[p++];
			}
		}
		sum[k%2]+=b;
		k++;
		prev = b;
		dbg(k, b, p, q, sum[0], sum[1]);
	}
	cout << k << " " << sum[0] << " " << sum[1] << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
