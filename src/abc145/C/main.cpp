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

double dfs(int v, int s, vector<ll> &x, vector<ll> &y){
	int n = x.size();
	int k = 0;
	for(int i=0; i<n; i++) if((s>>i)&1) k++;
	ll f = 1;
	for(int i=0; i<n-k-1; i++) f*=i+1;
	double ret = 0;
	for(int i=0; i<n; i++){
		if((s>>i)&1) continue;
		ret += dfs(i, s|(1<<i), x, y);
		ret += f*sqrt((x[v]-x[i])*(x[v]-x[i])+(y[v]-y[i])*(y[v]-y[i]));
	}
	return ret;
}

int main() {
	long long N;
    scanf("%lld",&N);
    std::vector<long long> x(N);
    std::vector<long long> y(N);
    for(int i = 0 ; i < N ; i++){
        scanf("%lld",&x[i]);
        scanf("%lld",&y[i]);
    }

	double sum = 0;
	ll fact = 1;
	for(int i=0; i<N; i++){
		sum += dfs(i, 1<<i, x, y);
		fact *= i+1;
	}
	cout << setprecision(20) << sum/fact << endl;
	return 0;
}
