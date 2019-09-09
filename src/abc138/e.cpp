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
	string S, T;
	cin >> S;
	cin >> T;

	int ns = S.size();
	int nt = T.size();
	vector<vector<int>> idx(26);
	for(int i=0; i<ns; i++){
		idx[S[i]-'a'].push_back(i);
	}

	ll cur = 0;
	ll cnt = 0;
	for(int i=0; i<nt; i++){
		if(idx[T[i]-'a'].size()==0) {
			cout << -1 << endl;
			return 0;
		}
		auto it = lower_bound(idx[T[i]-'a'].begin(), idx[T[i]-'a'].end(), cur);
		if(it==idx[T[i]-'a'].end()){
			cur = idx[T[i]-'a'][0]+1;
			cnt++;
		} else {
			cur = *it+1;
		}
	}

	cout << cnt*ns+cur << endl;

	return 0;
}
