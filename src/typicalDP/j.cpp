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

const double INF = 1e100;
int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;
	int n;
	cin >> n;
	int s = 0;
	for(int i=0; i<n; i++){
		int x; cin >> x;
		s += 1<<x;
	}

	vector<pair<int, int>> xs;
	for(int i=1; i<(1<<16); i++){
		int b=i;
		int m=0;
		while(b>0){
			m+=b&1;
			b>>=1;
		}
		xs.push_back({m, i});
	}

	sort(xs.begin(), xs.end());

	vector<double> dp(1<<16);

	for(auto p: xs){
		int x = p.second;
		dp[x] = INF;

		for(int i=1; i<15; i++){
			int c = 0;
			double p = 0;
			for(int k=-1; k<2; k++){
				if(x>>(i+k)&1){
					c++;
					p+=dp[x^(1<<(i+k))];
				}
			}
			if(c){
				dp[x] = min(dp[x], (3 + p)/c);
			}
		}
	}

	cout << dp[s] << endl;

	return 0;
}
