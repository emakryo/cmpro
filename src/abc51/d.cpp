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
const int INF = 1e8;
int main(){
	int N, M;
	cin >> N >> M;
	vector<int> A(M), B(M), C(M);
	vector<vector<int>> X(N, vector<int>(N, INF));
	for(int i=0; i<M; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		X[a][b] = c;
		X[b][a] = c;
		A[i] = a;
		B[i] = b;
		C[i] = c;
	}
	for(int i=0; i<N; i++) X[i][i] = 0;

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				X[i][j] = min(X[i][j], X[i][k]+X[k][j]);
			}
		}
	}

	int ans = 0;
	for(int i=0; i<M; i++) if(X[A[i]][B[i]] < C[i]) ans++;
	cout << ans << endl;

	return 0;
}
