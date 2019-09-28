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

int cnt[6002][6002];
int main(){
	int N;
	cin >> N;
	vector<int> X(N), Y(N), D(N);
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i] >> D[i];
	}

	vector<int> x(N), y(N);
	for(int i=0; i<N; i++){
		x[i] = X[i]-Y[i]+3000;
		y[i] = X[i]+Y[i];
		debug(x[i]+1, y[i]+1);
		cnt[x[i]+1][y[i]+1]++;
	}

	for(int i=1; i<6002; i++) for(int j=1; j<6002; j++){
		cnt[i][j] = cnt[i][j]+cnt[i][j-1]+cnt[i-1][j]-cnt[i-1][j-1];
	}

	for(int i=0; i<N; i++){
		int rx = min(6001, x[i]+1+D[i]);
		int lx = max(1, x[i]+1-D[i]);
		int uy = min(6001, y[i]+1+D[i]);
		int ly = max(1, y[i]+1-D[i]);
		//debug(rx, lx, uy, ly, cum[rx][uy], cum[rx][ly-1], cum[lx-1][uy], cum[lx-1][ly-1]);
		cout << cnt[rx][uy] - cnt[rx][ly-1] - cnt[lx-1][uy] + cnt[lx-1][ly-1] << endl;
	}

	return 0;
}
