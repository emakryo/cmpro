#include<bits/stdc++.h>

int chromatic_number(std::vector<std::vector<bool>> &adj){
	int n = adj.size();
	std::vector<int> dp(1<<n, 1e9);

	for(int s=1; s<(1<<n); s++){
		bool ok = true;
		for(int i=0; i<n; i++){
			if((s>>i&1)==0) continue;
			for(int j=i+1; j<n; j++){
				if((s>>j&1)==0) continue;
				if(adj[i][j]) ok=false;
			}
		}
		if(ok){
			dp[s] = 1;
			continue;
		}

		for(int t=(s-1)&s; t>0; t=(t-1)&s){
			int u=s^t;
			dp[s] = std::min(dp[s], dp[u]+dp[t]);
		}
	}

	return dp[(1<<n)-1];
}
