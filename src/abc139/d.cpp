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
	ll N;
	cin >> N;

	cout << (N-1)*N/2 << endl;

	return 0;
}
