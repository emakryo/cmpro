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

int main() {
	long long N;
    scanf("%lld",&N);
    std::string S;
    std::cin >> S;

	if(N%2==0){
		bool ok = true;
		for(int i=0; i<N/2; i++) ok = ok && S[i]==S[i+N/2];
		cout << (ok ? "Yes" : "No") << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}
