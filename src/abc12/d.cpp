#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int INF = 1e9;
int main(){
	int N, M;
	cin >> N >>M;
	vector<vector<int>> A(N, vector<int>(N, INF));
	for(int i=0; i<M; i++){
		int a, b, t;
		cin >> a >> b >> t;
		a--; b--;
		A[a][b] = t;
		A[b][a] = t;
	}

	for(int i=0; i<N; i++) A[i][i] = 0;
	for(int k=0; k<N; k++) for(int i=0; i<N; i++) for(int j=0; j<N; j++){
		A[i][j] = min(A[i][j], A[i][k]+A[k][j]);
	}

	int ans = INF;
	for(int i=0; i<N; i++){
		int x = 0;
		for(int j=0; j<N; j++){
			if(i==j) continue;
			x = max(x, A[i][j]);
		}
		ans = min(ans, x);
	}
	cout << ans << endl;


	return 0;
}
