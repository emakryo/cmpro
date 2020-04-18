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
	int A, B, M;
	cin >> A >> B >> M;
	vector<int> a(A), b(B), x(M), y(M), c(M);
	for(int i=0; i<A; i++) cin >> a[i];
	for(int i=0; i<B; i++) cin >> b[i];
	for(int i=0; i<M; i++) cin >> x[i] >> y[i] >> c[i];

	int min_a = a[0];
	for(int i=0; i<A; i++) min_a = min(min_a, a[i]);
	int min_b = b[0];
	for(int i=0; i<B; i++) min_b = min(min_b, b[i]);

	int min_m = a[x[0]-1]+b[y[0]-1]-c[0];
	for(int i=0; i<M; i++) min_m = min(min_m, a[x[i]-1]+b[y[i]-1]-c[i]);

	cout << min(min_a+min_b, min_m) << endl;

	return 0;
}
