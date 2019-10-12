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

int main(){
	int N;
	cin >> N;
	vector<vector<int>> adj(N, vector<int>(N));
	for(int i=0; i<N; i++){
		string s;
		cin >> s;
		for(int j=0; j<N; j++){
			if(i==j) adj[i][j] = 0;
			else if(s[j]=='1') adj[i][j] = 1;
			else adj[i][j] = 1e9;
		}
	}

	vector<vector<int>> dist(N, vector<int>(N));
	for(int i=0; i<N; i++) for(int j=0; j<N; j++) dist[i][j] = adj[i][j];
	for(int k=0; k<N; k++) for(int i=0; i<N; i++) for(int j=0; j<N; j++){
		dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
	}

	int ans = -1;
	for(int i=0; i<N; i++){
		debug("dist ", i);
		debugv(dist[i]);
		vector<vector<int>> hist(N);
		for(int j=0; j<N; j++){
			hist[dist[i][j]].push_back(j);
		}
		bool ok = true;
		for(int d=0; d<N; d++){
			if(hist[d].size()==0) continue;
			debug("hist ", d);
			debugv(hist[d]);
			for(int j=0; j<hist[d].size(); j++) for(int k=j+1; k<hist[d].size(); k++){
				if(adj[hist[d][j]][hist[d][k]]==1) ok = false;
			}
		}
		if(!ok) continue;
		int d = 0;
		while(d<N&&hist[d].size()>0) d++;
		ans = max(ans, d);
	}
	
	cout << ans << endl;

	return 0;
}
