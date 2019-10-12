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
	int N, K;
	cin >> N >> K;
	vector<ll> X(N), Y(N);
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
	}

	vector<pair<ll, int>> xi(N), yi(N);
	for(int i=0; i<N; i++){
		xi[i] = {X[i], i};
		yi[i] = {Y[i], i};
	}
	sort(xi.begin(), xi.end());
	sort(yi.begin(), yi.end());
	vector<int> xc(N), yc(N);
	for(int i=0; i<N; i++){
		xc[xi[i].second] = i;
		yc[yi[i].second] = i;
	}

	vector<vector<int>> cnt(N+1, vector<int>(N+1));
	for(int i=0; i<N; i++){
		cnt[xc[i]+1][yc[i]+1]++;
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			cnt[i][j] += cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
		}
	}

	ll ans = 4e18;
	for(int xl=0; xl<N; xl++) for(int xh=xl+1; xh<N; xh++){
		for(int yl=0; yl<N; yl++) for(int yh=yl+1; yh<N; yh++){
			int n = cnt[xh+1][yh+1]-cnt[xh+1][yl]-cnt[xl][yh+1]+cnt[xl][yl];
			if(n<K) continue;
			ans = min(ans, (xi[xh].first-xi[xl].first)*(yi[yh].first-yi[yl].first));
		}
	}
	cout << ans << endl;

	return 0;
}
