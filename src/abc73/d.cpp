#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int N, M, R;
vector<int> rs;
vector<vector<int>> A;
int dfs(int k, int s){
	debug(k, s);
	s += 1<<k;
	if(s==(1<<R)-1) return 0;
	int ret = 1e9;
	for(int i=0; i<R; i++){
		if((s>>i)&1) continue;
		ret = min(ret, dfs(i, s)+A[rs[i]][rs[k]]);
	}
	debug(k, s, ret);
	return ret;
}

int main(){
	cin >> N >> M >> R;
	rs.assign(R, 0);
	for(int i=0; i<R; i++){
		cin >> rs[i];
		rs[i]--;
	}
	A.assign(N, vector<int>(N, 1e9));
	for(int i=0; i<M; i++){
		int a, b, c;
		cin >> a >> b >> c;
		A[a-1][b-1] = c;
		A[b-1][a-1] = c;
	}

	for(int k=0; k<N; k++) for(int i=0; i<N; i++) for(int j=0; j<N; j++){
		A[i][j] = min(A[i][j], A[i][k]+A[k][j]);
	}

	int ans = 1e9;
	int s=0;
	for(int i=0; i<R; i++) ans = min(ans, dfs(i, s));
	cout << ans << endl;

	return 0;
}
