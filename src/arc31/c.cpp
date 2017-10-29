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
const int Nmax = 100000;
int N, B[Nmax];

template <class T>
class Bit{
	vector<T> v;
	public:
	Bit(int n) {
		v = vector<T>(n);
	}
	T sum(int i){
		int s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}

	void add(int i, T x){
		while(i <= v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> B[i];
	}

	vector<pair<int, int> > vec;
	for(int i=0; i<N; i++){
		vec.push_back(make_pair(B[i], i+1));
	}
	sort(vec.begin(), vec.end());

	Bit<ll> bit(N+1);
	for(int i=1; i<=N; i++){
		bit.add(i, 1);
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		int j=vec[i].second;
		ll left = bit.sum(j-1);
		ll right = bit.sum(N) - bit.sum(j);
		ans += min(left, right);
		bit.add(j, -1);
	}

	cout << ans << endl;

	return 0;
}
