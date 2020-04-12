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
	int N, K;
	cin >> N >> K;
	vector<int> P(N);
	for(int i=0; i<N; i++) cin >> P[i];

	vector<double> exp(N);
	for(int i=0; i<N; i++) exp[i] = (1+P[i])*0.5;

	double sum = 0;
	for(int i=0; i<K; i++) sum += exp[i];
	double ans = sum;
	for(int i=K; i<N; i++){
		sum += exp[i] - exp[i-K];
		ans = max(ans, sum);
	}

	cout << setprecision(10) << ans << endl;

	return 0;
}
