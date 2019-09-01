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
	vector<vector<int>> A(N, vector<int>(N-1));
	for(int i=0; i<N; i++){
		for(int j=0; j<N-1; j++){
			cin >> A[i][j];
		}
	}

	int n = 0;
	vector<int> idx(N, 0);
	vector<int> changed;
	for(int i=0; i<N; i++) changed.push_back(i);
	while(true){
		set<int> done;
		vector<int> next;
		bool update = false;
		for(int i: changed){
			if(done.count(i) > 0 || idx[i]==N-1) continue;
			int k = A[i][idx[i]]-1;
			if(done.count(k) > 0 || idx[k]==N-1) continue;
			if(A[k][idx[k]] == i+1){
				next.push_back(i);
				next.push_back(k);
				idx[i]++;
				idx[k]++;
				done.insert(i);
				done.insert(k);
				update = true;
				debug(any{n, i+1, k+1});
			}
		}
		changed = next;
		if(!update) break;
		n++;
	}

	bool ok = true;
	for(int i=0; i<N; i++){
		if(idx[i] != N-1) ok = false;
	}
	if(ok) cout << n << endl;
	else cout << -1 << endl;

	return 0;
}
