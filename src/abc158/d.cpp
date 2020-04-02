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
	int Q;
	cin >> Q;
	string X, Y;
	bool rev = false;
	for(int i=0; i<Q; i++){
		int t;
		cin >> t;
		if(t==1){
			rev = !rev;
			continue;
		}
		int f;
		string c;
		cin >> f >> c;
		if(f==1 && rev || f==2 && !rev){
			Y.append(c);
		} else {
			X.append(c);
		}
	}

	if(!rev){
		reverse(X.begin(), X.end());
		cout << X << S << Y << endl;
	} else {
		reverse(S.begin(), S.end());
		reverse(Y.begin(), Y.end());
		cout << Y << S << X << endl;
	}

	return 0;
}
