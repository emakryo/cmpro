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
	int N, K;
	cin >> N >> K;
	string S;
	cin >> S;

	int x=0, o=0;
	int ans = 0;
	for(int i=0; i<N-1; i++){
		if(S[i]=='R'&&S[i+1]=='L') x++;
		else if(S[i]=='L'&&S[i+1]=='R') o++;
	}

	for(int i=0; i<N; i++){
		if(i<N-1&&S[i]=='R'&&S[i+1]=='R') ans++;
		else if(i>0&&S[i]=='L'&&S[i-1]=='L') ans++;
	}

	debug(any{x, o, ans});
	if(2*K<x+o){
		cout << ans + 2*K << endl;
	} else {
		cout << ans + x + o << endl;
	}

	return 0;
}
