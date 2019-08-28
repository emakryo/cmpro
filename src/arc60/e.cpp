#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	cin >> N;
	vector<ll> X(N);
	for(int i=0; i<N; i++) cin >> X[i];
	ll L;
	cin >> L;

	vector<vector<ll>> skip(N, vector<ll>(20));
	int j=0;
	for(int i=0; i<N-1; i++){
		while(j<N&&X[j]-X[i]<=L) j++;
		skip[i][0] = j-1;
		debug(any{i, 0, j-1});
	}
	skip[N-1][0] = N;
	for(int n=1; n<20; n++){
		for(int i=0; i<N; i++){
			if(skip[i][n-1]<N) skip[i][n] = skip[skip[i][n-1]][n-1];
			else skip[i][n] = N;
			debug(any{i, n, skip[i][n]});
		}
	}

	int Q;
	cin >> Q;
	for(int q=0; q<Q; q++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		if(a>b) swap(a, b);

		int x=a;
		int k=19;
		int ans = 0;
		while(x<b){
			if(k>0&&skip[x][k]>b) k--;
			else {
				x = skip[x][k];
				ans += 1<<k;
			}
		}
		cout << ans << endl;
	}

	return 0;
}
