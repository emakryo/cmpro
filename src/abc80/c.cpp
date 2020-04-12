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
	vector<int> F(N);
	for(int i=0; i<N; i++){
		for(int j=0; j<10; j++){
			int f;
			cin >> f;
			F[i] += f<<j;
		}
	}

	vector<vector<int>> P(N, vector<int>(11));
	for(int i=0; i<N; i++){
		for(int j=0; j<11; j++){
			cin >> P[i][j];
		}
	}

	ll ans = -1e12;
	for(int s=1; s<(1<<10); s++){
		ll sum = 0;
		for(int i=0; i<N; i++){
			int a = s & F[i];
			ll cnt = 0;
			for(int k=0; k<10; k++){
				if((a>>k)&1) cnt++;
			}
			debug(s, i, a, cnt, P[i][cnt]);
			sum += P[i][cnt];
		}
		ans = max(ans, sum);
		debug(ans);
	}

	cout << ans << endl;
	return 0;
}
