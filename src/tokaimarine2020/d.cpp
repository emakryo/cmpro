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
	vector<int> v(n), w(n);
	for(int i=0; i<n; i++) cin >> v[i] >> w[i];
	int q; cin >> q;
	vector<int> u(q), l(q);
	for(int i=0; i<q; i++) cin >> u[i] >> l[i];

	vector<vector<pair<int, int>>> xs;

	const int H = 12;
	xs.push_back(vector<pair<int, int>>{{0, 0}, {w[0], v[0]}});
	for(int i=1; i<min(n, 1<<H); i++){
		vector<pair<int, int>> x(xs[(i-1)/2]);
		int m = x.size();
		for(int j=0; j<m; j++){
			x.push_back({x[j].first+w[i], x[j].second+v[i]});
		}
		sort(x.begin(), x.end());
		for(int j=1; j<x.size(); j++){
			x[j].second = max(x[j].second, x[j-1].second);
		}

		xs.push_back(x);
	}

	for(int i=0; i<q; i++){
		u[i]--;
		if(u[i]<(1<<H)){
			int ans = 0;
			int k = lower_bound(xs[u[i]].begin(), xs[u[i]].end(), pair<int, int>{l[i]+1, 0})-xs[u[i]].begin();
			if(k>0) ans = xs[u[i]][k-1].second;
			cout << ans << endl;
			continue;
		}

		vector<pair<int, int>> y(1, {0, 0});
		int t = u[i];
		while(t>=(1<<H)){
			int m = y.size();
			for(int j=0; j<m; j++){
				y.push_back({y[j].first+w[t], y[j].second+v[t]});
			}
			t = (t-1)/2;
		}

		int ans = 0;
		for(auto p: y){
			int k = lower_bound(xs[t].begin(), xs[t].end(), pair<int, int>{l[i]-p.first+1, 0}) - xs[t].begin();
			if(k==0) continue;
			ans = max(ans, p.second+xs[t][k-1].second);
		}
		cout << ans << endl;
	}

	return 0;
}
