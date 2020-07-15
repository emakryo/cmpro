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

	int n; cin>>n;
	string x; cin >> x;

	int k = 0;
	for(int i=0; i<n; i++){
		if(x[i]=='1') k++;
	}
	vector<int> r0(n), r1(n);
	if(k>2) r0[0] = 1;
	if(k>0) r1[0] = 1;
	for(int i=1; i<n; i++){
		if(k>1) r0[i] = r0[i-1]*2%(k-1);
		r1[i] = r1[i-1]*2%(k+1);
	}
	int x0 = 0, x1 = 0;
	for(int i=0; i<n; i++){
		if(x[i]=='1'){
			if(k>1) x0 = (x0+r0[n-1-i])%(k-1);
			x1 = (x1+r1[n-1-i])%(k+1);
		}
	}

	vector<int> y(n);
	for(int i=0; i<n; i++){
		if(x[i]=='1'){
			if(k>1) y[i] = (x0 + k-1 - r0[n-1-i])%(k-1);
		} else {
			y[i] = (x1 + r1[n-1-i])%(k+1);
		}
	}
	dbg(r0);
	dbg(r1);
	dbg(k, x0, x1);
	dbg(y);

	vector<int> ans(n);

	for(int i=0; i<n; i++){
		if(k==1&&x[i]=='1'){
			continue;
		}

		int z = y[i];
		int m = 1;
		while(z){
			int l = 0;
			int zz = z;
			while(zz){
				l+=zz&1;
				zz >>= 1;
			}
			z %= l;
			m++;
		}
		ans[i] = m;
	}

	for(int i=0; i<n; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
