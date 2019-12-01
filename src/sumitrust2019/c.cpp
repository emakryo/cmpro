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
	int X;
	cin >> X;

	vector<bool> dp(X+1, 0);
	dp[0] = true;
	for(int i=1; i<=X; i++){
		for(int x=100; x<=105; x++){
			if(i-x>=0 && dp[i-x]){
				dp[i] = true;
				break;
			}
		}
	}

	cout << (dp[X]?1:0) << endl;

	return 0;
}
