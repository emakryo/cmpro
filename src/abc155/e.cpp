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

ll dp[1000005][2];
int main(){
	string N;
	cin >> N;

	dp[0][0] = 0;
	dp[0][1] = 1;
	for(int i=0; i<N.size(); i++){
		int d = N[i]-'0';
		dp[i+1][0] = dp[i][0] + d;
		if(d > 0) dp[i+1][0] = min(dp[i+1][0], dp[i][1] + 10 - d);

		dp[i+1][1] = dp[i][1] + 9 - d;
		if(d < 9) dp[i+1][1] = min(dp[i+1][1], dp[i][0] + d + 1);


		debug(i, d, dp[i+1][0], dp[i+1][1]);
	}
	cout << dp[N.size()][0] << endl;

	return 0;
}
