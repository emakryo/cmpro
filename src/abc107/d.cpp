#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
ll N;
ll A[Nmax];

template <class T>
class Bit{
	vector<T> v;
	public:
	Bit(int n) {
		v = vector<T>(n);
	}
	// i must be 0 <= i < n
	T sum(int i){
		T s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}
	// i must be 1 <= i < n
	void add(int i, T x){
		while(i < v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	ll lb=0, ub=1e9+5;
	vector<ll> cum(N+1);
	while(ub-lb>1){
		ll x = (lb+ub)/2;
		for(int i=0; i<N; i++){
			cum[i+1] = cum[i]+(A[i]>=x?1:-1);
		}
		ll c = 0;
		Bit<int> bit(2*N+2);
		for(int i=0; i<=N; i++){
			c += bit.sum(1+N+cum[i]);
			bit.add(1+N+cum[i], 1);
			if(1+N+cum[i]<=0 || 1+N+cum[i]>=2*N+2)
				cout << x << " " << i << " " << 1+N+cum[i] << endl;
		}
		//cout << x << " " << c << endl;
		if(c >= (1+N*(N+1)/2)/2){
			lb = x;
		} else {
			ub = x;
		}
	}

	cout << lb << endl;

	return 0;
}
