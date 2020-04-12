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

struct state {
	ll n1, n2, n3;
	ll en1, en2, en3;
};

int main(){
	string S;
	cin >> S;
	int K;
	cin >> K;

	vector<state> dp(S.size());

	dp[0].en1 = 1;
	dp[0].n1 = S[0]-'1';
	dp[0].en2 = dp[0].en3 = dp[0].n2 = dp[0].n3 = 0;
	for(int i=1; i<S.size(); i++){
		dp[i].en1 = S[i]=='0'?dp[i-1].en1:0;
		dp[i].en2 = S[i]=='0'?dp[i-1].en2:dp[i-1].en1;
		dp[i].en3 = S[i]=='0'?dp[i-1].en3:dp[i-1].en2;

		dp[i].n1 = dp[i-1].n1 + 9 + (S[i]=='0'?0:dp[i-1].en1);
		dp[i].n2 = dp[i-1].n2 + dp[i-1].n1 * 9 + dp[i-1].en1 * max(S[i]-'1', 0)
			+ (S[i]=='0'?0:dp[i-1].en2);
		dp[i].n3 = dp[i-1].n3 + dp[i-1].n2 * 9 + dp[i-1].en2 * max(S[i]-'1', 0)
			+ (S[i]=='0'?0:dp[i-1].en3);
		debug(i, dp[i].en1, dp[i].en2, dp[i].en3, dp[i].n1, dp[i].n2, dp[i].n3);
	}

	state s = dp[S.size()-1];
	if(K==1) cout << s.n1 + s.en1 << endl;
	if(K==2) cout << s.n2 + s.en2 << endl;
	if(K==3) cout << s.n3 + s.en3 << endl;

	return 0;
}
