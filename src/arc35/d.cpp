#include<iostream>
#include<sstream>
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
const int Xmax = 5e6;
const int Nmax = 3e5;
int N, Q;
int p[Nmax], q[Nmax];
double cum_log[Xmax];

double log_cmb(int n, int m){
	return cum_log[n] - cum_log[m] - cum_log[n-m];
}

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
		while(i <= v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> p[i] >> q[i];

	for(int i=2; i<Xmax; i++){
		cum_log[i] += cum_log[i-1] + log(i);
	}

	vector<double> logc(N);
	for(int i=1; i<N; i++){
		logc[i] = log_cmb(p[i]-p[i-1]+q[i]-q[i-1], p[i]-p[i-1]);
	}

	Bit<double> bit(N);
	for(int i=1; i<N; i++){
		bit.add(i, logc[i]);
	}

	//for(int i=1; i<N; i++) cout << exp(bit.sum(i)) << endl;

	cin >> Q;
	stringstream ans;
	for(int i=0; i<Q; i++){
		int t;
		cin >> t;
		if(t == 1){
			int k, a, b;
			cin >> k >> a >> b;
			k--;
			p[k] = a; q[k] = b;
			if(k > 0){
				double l = log_cmb(p[k]-p[k-1]+q[k]-q[k-1], p[k]-p[k-1]);
				bit.add(k, l-logc[k]);
				logc[k] = l;
			}
			if(k < N-1){
				double l = log_cmb(p[k+1]-p[k]+q[k+1]-q[k], p[k+1]-p[k]);
				bit.add(k+1, l-logc[k+1]);
				logc[k+1] = l;
			}
		}else{
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			double c1 = bit.sum(r1-1) - bit.sum(l1-1);
			double c2 = bit.sum(r2-1) - bit.sum(l2-1);
			ans << (c1 > c2 ? "FIRST\n" : "SECOND\n");
		}
	}

	cout << ans.str();

	return 0;
}
