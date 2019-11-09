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

const double PI = 3.141592653589793;

int main(){
	int A, B, C;
	cin >> A >> B >> C;
	double lb = 0, ub = 200;
	for(int i=0; i<100; i++){
		double t = (lb+ub)/2;
		double f = A*t+B*sin(C*t*PI)-100;
		//debug(lb, t, ub, f);
		if(f<0){
			lb = t;
		} else {
			ub = t;
		}
	}
	debug(lb, ub, ub-lb, A*lb+B*sin(C*lb*PI));
	cout << setprecision(20) << lb << endl;
	//double f = A*lb+B*sin(C*lb*PI)-100;
	//if(abs(f)>1e-6) debug(lb, f);

	return 0;
}
