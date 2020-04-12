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
	int R, C, K;
	cin >> R >> C >> K;
	vector<string> S(R);
	for(int i=0; i<R; i++) cin >> S[i];

	vector<vector<int>> cnt(R, vector<int>(C));
	vector<vector<int>> s(R, vector<int>(C));
	for(int i=0; i<R; i++) for(int j=0; j<C; j++){
		s[i][j] = S[i][j]=='o'?1:0;
		if(abs(i-K+1)+abs(j-K+1)<=K-1 && S[i][j]=='o') cnt[K-1][K-1]++;
	}

	for(int x=K; x<R-K+1; x++) {
		int y = K-1;
		cnt[x][K-1] = cnt[x-1][K-1];
		for(int k=-K+1; k<K; k++){
			int dy = k;
			int dx = k<0 ? k+K-1 : -k+K-1;
			cnt[x][K-1] += s[x+dx][K-1+k] - s[x-1-dx][K-1+k];
		}
		//printf("%i %i %i\n", x, y, cnt[x][K-1]);
	}

	for(int y=K; y<C-K+1; y++) for(int x=K-1; x<R-K+1; x++) {
		cnt[x][y] = cnt[x][y-1];
		for(int k=-K+1; k<K; k++){
			int dx = k;
			int dy = k<0 ? k+K-1 : -k+K-1;
			cnt[x][y] += s[x+dx][y+dy] - s[x+dx][y-1-dy];
		}
		//printf("%i %i %i\n", x, y, cnt[x][y]);
	}

	int area = 0;
	for(int k=-K+1; k<K; k++) area += k<0 ? 2*k+2*K-1 : -2*k+2*K-1;

	int ans = 0;
	for(int x=K-1; x<R-K+1; x++) for(int y=K-1; y<C-K+1; y++) {
		if(cnt[x][y]==area) ans++;
	}
	cout << ans << endl;

	return 0;
}
