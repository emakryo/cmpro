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
int N, K;
int C[Nmax], D[Nmax];

template <class T>
class SegmentTree{
	vector<T> v;
	T def;
	int n;
	public:
	template<class I>
	SegmentTree(I first, I last, T default_value){
		n = 1;
		def = default_value;
		while(n < last-first) n <<= 1;
		v = vector<T>(2*n-1, default_value);
		copy(first, last, v.begin()+n-1);
		for(int i=n-2; i>=0; i--)
			v[i] = merge(v[2*i+1], v[2*i+2]);
	}
	SegmentTree(vector<T> initial_data, T default_value):
	SegmentTree(initial_data.begin(), initial_data.end(), default_value){}
	void update(int idx, T val){
		idx += n-1;
		v[idx] = val;
		while(idx > 0){
			idx = (idx-1)/2;
			v[idx] = merge(v[2*idx+1], v[2*idx+2]);
		}
	}
	T q(int a, int b, int k, int l, int r){
		if(a<=l&&r<=b) return v[k];
		if(b<=l||r<=a) return def;
		return merge(q(a, b, 2*k+1, l, (l+r)/2), q(a, b, 2*k+2, (l+r)/2, r));
	}
	T query(int a, int b){
		return q(a, b, 0, 0, n);
	}
	T merge(T left, T right);
};

// Example

template <>
int SegmentTree<int>::merge(int a, int b){
	return max(a, b);
}

ll solve_easy(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> C[i];
	for(int i=0; i<N; i++) cin >> D[i];

	ll ans = 0;
	for(int l=0; l<N; l++){
		for(int r=l; r<N; r++){
			int cmax=C[l], dmax=D[l];
			for(int i=l; i<=r; i++){
				cmax = max(cmax, C[i]);
				dmax = max(dmax, D[i]);
			}
			//cout << l << " " << r << " " << cmax << " " << dmax << endl;
			if(abs(cmax-dmax)<=K) ans++;
		}
	}
	return ans;
}

ll solve(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> C[i];
	for(int i=0; i<N; i++) cin >> D[i];

	SegmentTree<int> c_max(C, C+N, 0), d_max(D, D+N, 0);
	ll ans = 0;

	for(int i=0; i<N; i++){
		if(C[i]>D[i]-K){
		}
	}

	return ans;
}



int main(){
	int t;
	cin >> t;
	for(int i=0; i<t; i++){
		ll ans = solve();
		cout << "Case #" << i+1 << ": " << ans << endl;
	}

	return 0;
}
