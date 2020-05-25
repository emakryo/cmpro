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

int main() {
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	vector<int> d(n);
	vector<pair<int, int>> e(m);
	vector<vector<pair<int, int>>> graph(n);
	for(int i=0; i<n; i++) cin >> d[i];
	for(int i=0; i<m; i++){
		cin >> e[i].first >> e[i].second;
		e[i].first--;
		e[i].second--;
		graph[e[i].first].push_back({e[i].second, i});
		graph[e[i].second].push_back({e[i].first, i});
	}

	vector<pair<int, int>> ds(n);
	for(int i=0; i<n; i++) ds[i] = {d[i], i};

	sort(ds.begin(), ds.end());

	vector<pair<int, int>> es;
	for(int i=0; i<m; i++){
		if(d[e[i].first]!=d[e[i].second]) continue;
		es.push_back({d[e[i].first], i});
	}
	sort(es.begin(), es.end());

	vector<int> c(n);
	vector<int> x(m, 1e9);

	for(int i=0; i<n; i++){
		int v=ds[i].second;
		if(c[v]>0) continue;
		bool done = false;
		for(auto p: graph[v]){
			int u = p.first;
			if(c[u]>0){
				c[v] = 3-c[u];
				x[p.second] = ds[i].first;
				done=true;
				break;
			}
		}
		if(done) continue;

		for(auto p: graph[v]){
			int u = p.first;
			if(d[u]==d[v]){
				c[u] = 1;
				c[v] = 2;
				x[p.second] = ds[i].first;
				done = true;
				break;
			}
		}
		if(!done){
			cout << -1 << endl;
			return 0;
		}
	}

	string ans;
	for(int i=0; i<n; i++){
		if(c[i]==1) ans += "B";
		else ans += "W";
	}
	cout << ans << endl;
	for(int i=0; i<m; i++){
		cout << x[i] << endl;
	}

	return 0;
}
