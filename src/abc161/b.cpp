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
	int N, M;
	cin >> N >> M;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	int sum = 0;
	for(int i=0; i<N; i++) sum += A[i];

	int cnt = 0;
	for(int i=0; i<N; i++) if(A[i]*4*M >= sum) cnt++;

	if(cnt>=M) cout << "Yes" << endl;
	else cout << "No" << endl;

	return 0;
}
