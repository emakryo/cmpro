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
	int H, W;
	cin >> H >> W;
	vector<string> S(H);

	for(int i=0; i<H; i++) cin >> S[i];

	vector<vector<int>> dp(H, vector<int>(W, 1e9));

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(i==0&&j==0){
				dp[i][j]=0;
				continue;
			}
			int dx[] = {0, 1};
			int dy[] = {1, 0};
			for(int k=0; k<2; k++){
				int px = i-dx[k];
				int py = j-dy[k];
				if(0<=px&&px<H&&0<=py&&py<W){
					dp[i][j] = min(dp[i][j], dp[px][py]+(S[i][j]==S[px][py]?0:1));
				}
			}
		}
	}

	if(S[0][0]=='.'&&S[H-1][W-1]=='.'){
		cout << dp[H-1][W-1]/2 << endl;
	} else if(S[0][0]=='#'&&S[H-1][W-1]=='#'){
		cout << dp[H-1][W-1]/2+1 << endl;
	} else {
		cout << (dp[H-1][W-1]+1)/2 << endl;
	}

	return 0;
}
