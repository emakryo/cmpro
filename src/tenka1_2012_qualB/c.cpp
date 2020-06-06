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
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int parse(string t){
	int h = atoi(t.substr(0, 2).c_str());
	int m = atoi(t.substr(3, 2).c_str());
	return 60*h+m;
}

int chromatic_number(vector<vector<bool>> &adj){
	int n = adj.size();
	vector<int> dp(1<<n, 1e9);

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
			dp[s] = min(dp[s], dp[u]+dp[t]);
		}
	}

	return dp[(1<<n)-1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n; cin >> n;
	vector<int> s(n), e(n);
	for(int i=0; i<n; i++){
		string ts, te;
		cin >> ts >> te;
		s[i] = parse(ts);
		e[i] = parse(te);
		dbg(s[i], e[i]);
	}

	vector<vector<bool>> adj(n, vector<bool>(n));
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(max(s[i], s[j])<min(e[i], e[j]) ||
				max(s[i], s[j]-24*60)<min(e[i], e[j]-24*60) ||
				max(s[i]-24*60, s[j])<min(e[i]-24*60, e[j])){
				adj[i][j] = adj[j][i] = true;
			}
		}
	}

	cout << chromatic_number(adj) << endl;
	return 0;
}
