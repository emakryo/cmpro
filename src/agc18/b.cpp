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

int main(){
	int N, M;
	cin >> N >> M;
	vector<vector<int>> A(N, vector<int>(M));
	for(int i=0; i<N; i++) for(int j=0; j<M; j++){
		cin >> A[i][j];
	}

	vector<vector<int>> belongs(M+1);
	for(int i=0; i<N; i++){
		belongs[A[i][0]].push_back(i);
	}
	vector<bool> removed(M+1);
	vector<int> idx(N, 0);
	int ans = 1e9;
	for(int i=0; i<M; i++){
		int m = 0;
		int k = 0;
		for(int j=1; j<=M; j++) if(m < belongs[j].size()) {
			m = belongs[j].size();
			k = j;
		}
		debug(any{k, m});
		ans = min(ans, m);

		removed[k] = true;
		for(int l: belongs[k]){
			idx[l]++;
			while(idx[l]<M && removed[A[l][idx[l]]]) idx[l]++;
			if(idx[l]==M) {
				cout << ans << endl;
				return 0;
			}
			belongs[A[l][idx[l]]].push_back(l);
		}
		belongs[k].clear();
	}
	cout << ans << endl;

	return 0;
}
