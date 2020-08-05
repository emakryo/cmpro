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

void dfs(int u, int p, vector<vector<int>> &graph, vector<int> &depth){
	depth[u] = depth[p]+1;

	for(int v: graph[u]){
		if(v==p) continue;
		dfs(v, u, graph, depth);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n; cin >> n;
	vector<vector<int>> graph(n);
	for(int i=0; i<n-1; i++){
		int a, b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> depth(n);
	dfs(0, -1, graph, depth);

	vector<int> ans(n);

	vector<int> ve, vo;

	for(int i=0; i<n; i++){
		if(depth[i]%2){
			ve.push_back(i);
		} else {
			vo.push_back(i);
		}
	}
	dbg(depth);

	if(ve.size()>vo.size()){
		swap(ve, vo);
	}

	vector<bool> used(n+1);
	if(ve.size()<=n/3){
		int m = 3;
		for(int v: ve){
			ans[v] = m;
			used[m] = true;
			m+=3;
		}

		int k=0;
		for(int i=1; i<=n; i++){
			if(!used[i]){
				ans[vo[k]] = i;
				k++;
			}
		}
	} else {
		for(int i=0; 3*i+1<=n; i++){
			ans[ve[i]] = 3*i+1;
			used[ve[i]] = true;
		}
		for(int i=0; 3*i+2<=n; i++){
			ans[vo[i]] = 3*i+2;
			used[vo[i]] = true;
		}
		int k = 1;
		for(int i=0; i<n; i++){
			if(!used[i]){
				ans[i] = 3*k;
				k++;
			}
		}
	}
	cout << ans << endl;

	return 0;
}
