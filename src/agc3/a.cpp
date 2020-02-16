#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	string S;
	cin >> S;

	int e=0,w=0,s=0,n=0;
	for(int i=0; i<S.size(); i++){
		if(S[i]=='E') e++;
		if(S[i]=='W') w++;
		if(S[i]=='S') s++;
		if(S[i]=='N') n++;
	}

	if(s>0&&n==0 || n>0&&s==0 || e>0&&w==0 || w>0&&e==0){
		cout << "No" << endl;
	} else {
		cout << "Yes" << endl;
	}


	return 0;
}
