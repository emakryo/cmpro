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
	string S;
	cin >> S;

	for(int i=0; i<S.size(); i++){
		if((i%2==0 && S[i]=='L') || (i%2 && S[i]=='R')){
			cout << "No" << endl;
			return 0;
		}
	}

	cout << "Yes" << endl;


	return 0;
}
