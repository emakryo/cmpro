#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;

template <class T, class E>
class LazySegmentTree{
public:
	vector<T> data, lazy;
	T def;
	E lazy_def;
	int n, height;
	LazySegmentTree(int n_, T def, E lazy_def):
	def(def), lazy_def(lazy_def){
		init(n_);
	}
	LazySegmentTree(const vector<T> &v, T def, E lazy_def):
	def(def), lazy_def(lazy_def){
		int n_ = v.size();
		init(n_);
		for(int i=0; i<n_; i++) data[n+i] = v[i];
		for(int i=n-1; i; i--) data[i] = merge(data[(i<<1)], data[(i<<1)|1]);
	}
	void init(int n_){
		n=1; height=0;
		while(n<n_) n<<=1, height++;
		data.assign(2*n, def);
		lazy.assign(2*n, lazy_def);
	}
	inline T reflect(int k){
		return lazy[k]==lazy_def?data[k]:apply(data[k], lazy[k]);
	}
	inline void eval(int k){
		if(lazy[k]==lazy_def) return;
		lazy[k<<1] = propagate(lazy[k<<1], lazy[k]);
		lazy[(k<<1)|1] = propagate(lazy[(k<<1)|1], lazy[k]);
		data[k] = reflect(k);
		lazy[k] = lazy_def;
	}
	inline void thrust(int k){
		for(int i=height; i; i--) eval(k>>i);
	}
	inline void recalc(int k){
		while(k>>=1) data[k] = merge(reflect(k<<1), reflect((k<<1)|1));
	}
	void update(int a, int b, E x){
		thrust(a+=n);
		thrust(a+=n-1);
		for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
			if(l&1) lazy[l] = propagete(lazy[l], x), l++;
			if(r&1) --r, lazy[r]=propagete(lazy[r], x);
		}
		recalc(a);
		recalc(b);
	}
	void set(int a, T x){
		thrust(a+=n);
		data[a] = x;
		lazy[a] = lazy_def;
		recalc(a);
	}
	T query(int a, int b){
		thrust(a+=n);
		thrust(a+=n-1);
		T vl = def, vr = def;
		for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
			if(l&1) vl = merge(vl, reflect(l++));
			if(r&1) vr = merge(reflect(--r), vr);
		}
		return merge(vl, vr);
	}
	T merge(T left, T right);
	E propagate(E left, E right);
	T apply(T val, E laz);
};

// Example

template <>
int LazySegmentTree<int, int>::merge(int a, int b){
	return min(a, b);
}

int main(){
	vector<int> a({4,2,2,1,5,9,10});
	LazySegmentTree<int, int> st(a, 1<<20, 0);
	cout << st.query(0, 4) << endl;
	for(int i=0; i<8; i++) cout << st.query(i, i+1) << endl;

	return 0;
}
