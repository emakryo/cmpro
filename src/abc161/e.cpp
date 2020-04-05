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
	int N, K, C;
	cin >> N >> K >> C;
	string S;
	cin >> S;

	vector<int> dp1(N+2), dp2(N+2);


	dp1[0] = 0;
	for(int i=0; i<N+1; i++){
		dp1[i+1] = S[i]=='o'?1:0;
		if(i>=C) dp1[i+1]+=dp1[i-C];
		dp1[i+1]=max(dp1[i], dp1[i+1]);
	}

	dp2[N+1] = 0;
	for(int i=N-1; i>=0; i--){
		dp2[i+1] = S[i]=='o'?1:0;
		if(i+C+2<N+2) dp2[i+1]+=dp2[i+C+2];
		dp2[i+1] = max(dp2[i+1], dp2[i+2]);
	}

	for(int i=0; i<N; i++){
		if(dp1[i]+dp2[i+2]<K) cout << i+1 << endl;
	}

	return 0;
}
