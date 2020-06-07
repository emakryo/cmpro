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

std::vector<int> vertex_coloring(std::vector<std::vector<bool>> &adj){
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

	std::vector<int> c(n, -1);
	int k=0;
	std::queue<long long> que;
	que.push((1<<n)-1);
	while(!que.empty()){
		long long s = que.front();
		que.pop();

		bool ok = true;
		for(int i=0; i<n; i++){
			if((s>>i&1)==0) continue;
			for(int j=i+1; j<n; j++){
				if((s>>j&1)==0) continue;
				if(adj[i][j]) ok = false;
			}
		}

		if(ok){
			for(int i=0; i<n; i++){
				if((s>>i&1)==0) continue;
				c[i] = k;
			}
			k++;
			continue;
		}

		for(int t=(s-1)&s; t>0; t=(t-1)&s){
			int u = s^t;
			if(dp[s]==dp[u]+dp[t]){
				que.push(u);
				que.push(t);
				break;
			}
		}
	}

	return c;
}
