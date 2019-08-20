#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" "; cout<<xs[xs.size()-1]<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

template <typename T, class E>
struct LazySegmentTree{
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
	T reflect(int k){
		return lazy[k]==lazy_def?data[k]:apply(data[k], lazy[k]);
	}
	void eval(int k){
		if(lazy[k]==lazy_def) return;
		lazy[k<<1] = propagate(lazy[k<<1], lazy[k]);
		lazy[(k<<1)|1] = propagate(lazy[(k<<1)|1], lazy[k]);
		data[k] = reflect(k);
		lazy[k] = lazy_def;
	}
	void thrust(int k){
		for(int i=height; i; i--) eval(k>>i);
	}
	void recalc(int k){
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
	T merge(T left, T right) const { return min(left, right); }
	E propagate(E before, E change) const { return before+change; }
	T apply(T val, E laz) const { return val+laz; }
};

int main(){
	int N, Q, A, B;
	cin >> N >> Q >> A >> B;
	vector<ll> X(Q+1);
	X[0] = B;
	for(int i=0; i<Q; i++) cin >> X[i+1];

	LazySegmentTree<ll, ll> st1(N+1, 1LL<<60, 0), st2(N+1, 1LL<<60, 0);
	st1.set(A, A);
	st2.set(A, -A);

	for(int i=0; i<Q; i++){
		ll t1 = min(st2.query(1, X[i+1])+X[i]+X[i+1], st1.query(X[i+1], N+1)+X[i]-X[i+1]);
		ll t2 = min(st2.query(1, X[i+1])-X[i]+X[i+1], st1.query(X[i+1], N+1)-X[i]-X[i+1]);
		debug(any{t1, t2});
		st1.update(1, N+2, abs(X[i+1]-X[i]));
		st2.update(1, N+2, abs(X[i+1]-X[i]));
		st1.set(X[i], min(st1.query(X[i], X[i]+1), t1));
		st2.set(X[i], min(st2.query(X[i], X[i]+1), t2));
	}
	ll ans = 1LL<<60;
	for(int i=1; i<=N; i++){
		ans = min(ans, (st1.query(i, i+1)+st2.query(i, i+1))/2);
	}
	cout << ans << endl;
	return 0;
}
