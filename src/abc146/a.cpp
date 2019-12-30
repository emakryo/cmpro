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

	vector<string> day = {
		"SAT",
		"FRI",
		"THU",
		"WED",
		"TUE",
		"MON",
		"SUN",
	};

	for(int i=0; i<7; i++){
		if(S==day[i]) {
			cout << i+1 << endl;
		}
	}

	return 0;
}
