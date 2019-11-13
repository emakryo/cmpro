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

int dp[2][51][10001];
int main(){
	int W, N, K;
	cin >> W >> N >> K;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++){
		cin >> A[i] >> B[i];
	}

	for(int i=0; i<2; i++){
		for(int j=0; j<=K; j++){
			for(int w=0; w<=W; w++){
				dp[i][j][w] = -100000;
			}
		}
	}
	dp[0][0][0] = 0;

	for(int i=0; i<N; i++){
		for(int j=0; j<=K; j++){
			for(int w=0; w<=W; w++){
				dp[1-i%2][j][w] = dp[i%2][j][w];
			}
		}
		for(int j=0; j<K; j++){
			for(int w=0; w<W; w++){
				if(w+A[i]<=W) dp[1-i%2][j+1][w+A[i]] = max(dp[1-i%2][j+1][w+A[i]], dp[i%2][j][w]+B[i]);
			}
		}
	}

	int ans = 0;
	for(int j=0; j<=K; j++){
		for(int w=0; w<=W; w++){
			debug(j, w, dp[N%2][j][w]);
			ans = max(dp[N%2][j][w], ans);
		}
	}

	cout << ans << endl;

	return 0;
}
