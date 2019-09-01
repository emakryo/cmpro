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
	vector<int> W(N);
	for(int i=0; i<N; i++) cin >> W[i];

	int wsum = 0;
	for(int i=0; i<N; i++) wsum += W[i];
	int wcum = 0;
	int ans = 1e8;
	for(int i=0; i<N; i++){
		wcum += W[i];
		ans = min(ans, abs(wsum-2*wcum));
	}
	cout << ans << endl;


	return 0;
}
