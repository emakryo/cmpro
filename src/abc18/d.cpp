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
	int N, M, P, Q, R;
	cin >> N >> M >> P >> Q >> R;
	vector<int> X(R), Y(R), Z(R);
	for(int i=0; i<R; i++){
		cin >> X[i] >> Y[i] >> Z[i];
		X[i]--; Y[i]--;
	}

	int ans = 0;
	for(int s=0; s<(1<<N); s++){
		int cnt = 0;
		for(int k=0; k<N; k++) cnt+=s>>k&1;
		if(cnt != P) continue;

		vector<int> sum(M);
		for(int i=0; i<R; i++){
			if(s>>X[i]&1) sum[Y[i]]+=Z[i];
		}

		sort(sum.rbegin(), sum.rend());
		int total = 0;
		for(int i=0; i<Q; i++) total += sum[i];

		ans = max(ans, total);
	}

	cout << ans << endl;

	return 0;
}
