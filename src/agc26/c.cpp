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
	string S;
	cin >> S;

	string tl = S.substr(0, N);
	string tr = S.substr(N, N);
	reverse(tr.begin(), tr.end());

	ll ans = 0;
	for(int i=0; i<(1<<N); i++){
		string red, blue;
		for(int k=0; k<N; k++){
			if((i>>k)&1) red += tl[k];
			else blue += tl[k];
		}
		int nr = red.size();
		int nb = blue.size();
		vector<vector<ll>> dp(nr+1, vector<ll>(nb+1));
		dp[0][0] = 1;
		for(int k=0; k<nr; k++){
			if(red[k]==tr[k]) dp[k+1][0] = dp[k][0];
		}
		for(int j=0; j<nb; j++){
			if(blue[j]==tr[j]) dp[0][j+1] = dp[0][j];
		}
		for(int k=0; k<nr; k++) for(int j=0; j<nb; j++){
			if(tr[k+j+1] == red[k]) dp[k+1][j+1] += dp[k][j+1];
			if(tr[k+j+1] == blue[j]) dp[k+1][j+1] += dp[k+1][j];
		}
		//for(int k=0; k<=nr; k++) debugv(dp[k]);
		debug(red, blue, tr, dp[nr][nb]);
		ans += dp[nr][nb];
	}

	cout << ans << endl;

	return 0;
}
