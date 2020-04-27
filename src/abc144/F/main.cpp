#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N, M;
	cin >> N >> M;
	vector<vector<int>> graph(N), rgraph(N);
	for(int i=0; i<M; i++){
		int s, t;
		cin >> s >> t;
		s--; t--;
		graph[s].push_back(t);
		rgraph[t].push_back(s);
	}

	double ans = 1e18;
	for(int i=N-1; i>=0; i--){
		vector<double> dp(N);
		for(int j=N-1; j>=0; j--){
			double dmax = 0;
			for(int t: graph[j]){
				dmax = max(dmax, dp[t]);
				dp[j] += dp[t]+1;
			}
			if(i==j && graph[j].size()>1){
				dp[j] -= dmax+1;
				dp[j] /= graph[j].size()-1;
			} else if(graph[j].size()>0){
				dp[j] /= graph[j].size();
			}
		}
		ans = min(ans, dp[0]);
	}
	
	cout << setprecision(20) << ans << endl;

	return 0;
}
