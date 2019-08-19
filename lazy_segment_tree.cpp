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

template <typename T, class E>
class LazySegmentTree{
public:
	vector<T> data, lazy;
	T def;
	E lazy_def;
	int n, height;
	LazySegmentTree(int n_, T def, E lazy_def): def(def), lazy_def(lazy_def){
		init(n_);
	}
	LazySegmentTree(const vector<T> &v, T def, E lazy_def): def(def), lazy_def(lazy_def){
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
		thrust(b+=n-1);
		for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
			if(l&1) lazy[l] = propagate(lazy[l], x), l++;
			if(r&1) --r, lazy[r]=propagate(lazy[r], x);
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
		thrust(b+=n-1);
		T vl = def, vr = def;
		for(int l=a, r=b+1; l<r; l>>=1, r>>=1){
			if(l&1) vl = merge(vl, reflect(l++));
			if(r&1) vr = merge(reflect(--r), vr);
		}
		return merge(vl, vr);
	}

	// Example (min, add)
	T merge(T left, T right) { return min(left, right); }
	E propagate(E before, E change) { return before+change; }
	T apply(T val, E laz) { return val+laz; }
};

int main(){
	vector<int> a({4,2,2,1,5,9,10});
	LazySegmentTree<int, int> st(a, 1<<20, 0);
	cout << st.query(0, 4) << endl;
	for(int i=0; i<8; i++) cout << st.query(i, i+1) << endl;
	st.set(3, 8);
	cout << st.query(0, 4) << endl;
	for(int i=0; i<8; i++) cout << st.query(i, i+1) << endl;
	st.update(2, 6, 8);
	st.update(5, 7, -3);
	cout << st.query(0, 4) << endl;
	for(int i=0; i<8; i++) cout << st.query(i, i+1) << endl;

	return 0;
}
