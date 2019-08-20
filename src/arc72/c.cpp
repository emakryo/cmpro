#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout << xs[i] << " ";
	cout << xs[xs.size()-1] << endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];
	vector<ll> cum1(N), cum2(N);
	cum1[0] = max(1LL, A[0]);
	cum2[0] = min(-1LL, A[0]);
	for(int i=1; i<N; i++){
		if(i%2){
			cum1[i] = min(-1LL, cum1[i-1]+A[i]);
			cum2[i] = max(1LL, cum2[i-1]+A[i]);
		} else {
			cum1[i] = max(1LL, cum1[i-1]+A[i]);
			cum2[i] = min(-1LL, cum2[i-1]+A[i]);
		}
	}

	ll a1=abs(cum1[0]-A[0]), a2=abs(cum2[0]-A[0]);
	for(int i=1; i<N; i++){
		a1 += abs(cum1[i]-cum1[i-1]-A[i]);
		a2 += abs(cum2[i]-cum2[i-1]-A[i]);
	}
	cout << min(a1, a2) << endl;
	return 0;
}
