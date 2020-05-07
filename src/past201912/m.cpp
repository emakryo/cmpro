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

double solve(vector<int> &a, vector<int> &b){
	double lb=0, ub=1e10;
	for(int q=0; q<100; q++){
		double x = (lb+ub)/2;
		vector<double> v;
		for(int i=0; i<a.size(); i++){
			v.push_back(b[i]-x*a[i]);
		}
		sort(v.rbegin(), v.rend());
		double s=0;
		for(int i=0; i<5; i++) s+=v[i];
		dbg(x, s);
		if(s>0){
			lb = x;
		} else{
			ub = x;
		}
	}
	return ub;
}


int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<int> a(n), b(n), c(m), d(m);
	for(int i=0; i<n; i++) cin >> a[i] >> b[i];
	for(int i=0; i<m; i++) cin >> c[i] >> d[i];

	double ans = 0;
	for(int i=0; i<m; i++){
		a.push_back(c[i]);
		b.push_back(d[i]);
		ans = max(solve(a, b), ans);
		a.pop_back();
		b.pop_back();
	}

	cout << setprecision(20) << ans << endl;

	return 0;
}
