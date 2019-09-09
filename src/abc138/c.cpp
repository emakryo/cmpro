#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
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
	vector<int> V(N);
	for(int i=0; i<N; i++) cin >> V[i];

	sort(V.begin(), V.end());
	double ans = V[0];
	double ans2 = (double)V[0]/(1LL<<(N-1));
	for(int i=1; i<N; i++){
		ans = (ans+V[i])/2;
		ans2 += (double)V[i]/(1LL<<(N-i));
	}
	cout << setprecision(20) << ans << " " << ans2 << " " << ans-ans2 << endl;

	return 0;
}
