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
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> cum(N);
	cum[0] = A[0];
	for(int i=1; i<N; i++) cum[i]=A[i]+cum[i-1];

	int n=0;
	while(n<N && cum[n]<cum[N-1]/2) n++;
	if(n < N && cum[n]==cum[N-1]/2){
		cout << 0 << endl;
		return 0;
	}
	ll a = n == N ? cum[N-1] : cum[n];
	ll b = n > 0 ? cum[n-1] : 0;


	cout << min(a-(cum[N-1]-a), cum[N-1]-b-b) << endl;

	return 0;
}
