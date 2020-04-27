#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int A, B, C, D;
	cin >> A >> B >> C >> D;
	while(true){
		C-=B;
		if(C<=0){
			cout << "Yes" << endl;
			return 0;
		}
		A-=D;
		if(A<=0){
			cout << "No" << endl;
			return 0;
		}
	}

	return 0;
}
