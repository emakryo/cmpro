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
	int N, M, Q;
	cin >> N >> M >> Q;

	vector<int> L(M), R(M);
	for(int i=0; i<M; i++) cin >> L[i] >> R[i];

	vector<vector<int>> cnt(N+1, vector<int>(N+1));
	for(int i=0; i<M; i++){
		cnt[L[i]][R[i]]++;
	}

	vector<vector<int>> cumsum(N+1, vector<int>(N+1));
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			cumsum[i][j] = cnt[i][j]+cumsum[i][j-1]+cumsum[i-1][j]-cumsum[i-1][j-1];
		}
	}

	for(int i=0; i<Q; i++){
		int p, q;
		cin >> p >> q;
		cout << cumsum[N][q] - cumsum[p-1][q] << endl;
	}

	return 0;
}
