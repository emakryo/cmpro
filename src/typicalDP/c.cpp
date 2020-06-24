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

double elo(int r1, int r2){
	return 1/(1+pow(10, (r2-r1)/400.0));
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int k; cin >> k;
	vector<int> r(1<<k);
	cin >> r;

	vector<double> dp(1<<k, 1);
	for(int j=0; j<k; j++){
		vector<double> next(1<<k);
		for(int i=0; i<(1<<k); i++){
			int l0 = i/(1<<j);
			if(l0%2){
				l0 = (l0-1)*(1<<j);
			} else {
				l0 = (l0+1)*(1<<j);
			}
			dbg(j, i, l0);
			for(int l=l0; l<l0+(1<<j); l++){
				next[i] += elo(r[i], r[l])*dp[i]*dp[l];
			}
		}
		dp = next;
	}

	for(int i=0; i<(1<<k); i++){
		cout << dp[i] << endl;
	}
	return 0;
}
