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

struct UnionFind{
	std::vector<int> par, rnk, cnt;
	UnionFind(int n){
		par.assign(n, 0);
		rnk.assign(n, 0);
		cnt.assign(n, 1);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i){
		if(par[i]==i) return i;
		return par[i]=root(par[i]);
	}
	void unite(int i, int j){
		int ri = root(i);
		int rj = root(j);
		if(ri==rj) return;

		if(rnk[ri]==rnk[rj]){
			cnt[rj] += cnt[ri];
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			cnt[rj] += cnt[ri];
			par[ri] = rj;
		}
		else{
			cnt[ri] += cnt[rj];
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
	int count(int i){
		return cnt[root(i)];
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<int> x(n+m), y(n+m), c(n+m);
	for(int i=0; i<n+m; i++) cin >> x[i]>>y[i]>>c[i];

	double ans = 1e18;
	for(int b=0; b<(1<<m); b++){
		UnionFind uf(n+m);
		vector<pair<double, pair<int, int>>> edge;
		for(int i=0; i<n+m; i++){
			for(int j=i+1; j<n+m; j++){
				double d = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
				if(c[i]!=c[j]){
					d *= 10;
				}
				if(i>=n){
					if((b>>(i-n)&1)==0) continue;
				}
				if(j>=n){
					if((b>>(j-n)&1)==0) continue;
				}
				edge.push_back({d, {i, j}});
			}
		}

		sort(edge.begin(), edge.end());
		double cost = 0;
		for(auto e: edge){
			int a = e.second.first;
			int b = e.second.second;
			if(uf.same(a,b)) continue;
			else {
				cost += e.first;
				uf.unite(a,b);
			}
		}
		ans = min(ans, cost);
	}


	cout << setprecision(20) << ans << endl;
	return 0;
}
