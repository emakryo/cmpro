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
	int N;
	cin >> N;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	bool ok=true;
	for(int i=0; i<N; i++){
		if(A[i]%2) continue;
		if(A[i]%3!=0 && A[i]%5!=0) ok=false;
	}

	if(ok) cout << "APPROVED" << endl;
	else cout << "DENIED" << endl;

	return 0;
}
