#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

class UnionFind{
	vector<int> par, rnk, cnt;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		cnt=vector<int>(n,1);
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

int main(){
	int N, M;
	cin >> N >> M;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	UnionFind uf(N);
	for(int i=0; i<M; i++){
		int x, y;
		cin >> x >> y;
		uf.unite(x, y);
	}

	map<int, vector<int>> connected;
	for(int i=0; i<N; i++){
		connected[uf.root(i)].push_back(i);
	}

	if(2*connected.size()-2>N){
		cout << "Impossible" << endl;
		return 0;
	} else if(connected.size()==1){
		cout << 0 << endl;
		return 0;
	}
	ll ans = 0;
	vector<ll> remain;
	for(auto p: connected){
		vector<int> v = p.second;
		vector<ll> va;
		for(int u: v) va.push_back(A[u]);
		sort(va.begin(), va.end());
		ans += va[0];
		for(int i=1; i<va.size(); i++) remain.push_back(va[i]);
	}
	sort(remain.begin(), remain.end());
	for(int i=0; i<(int)connected.size()-2; i++) ans += remain[i];
	debug(any{(int)connected.size(), (int)remain.size()});
	cout << ans << endl;

	return 0;
}
