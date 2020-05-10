#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

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
			if(l&1) lazy[l]=propagate(lazy[l], x), l++;
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

	T merge(T left, T right) const { return left+right; }
	E propagate(E before, E change) const { return before+change; }
	T apply(T val, E laz) const { return val+laz; }
};

int _main(){
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

int main() {
	ios_base::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	vector<ll> x(n), y(n), d(n), c(n);
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i] >> d[i] >> c[i];
	}
	vector<ll> a(q), b(q);
	for(int i=0; i<q; i++){
		cin >> a[i] >> b[i];
	}
	map<ll, int> xs;
	for(int i=0; i<n; i++){
		xs[x[i]] = 0;
		xs[x[i]+d[i]] = 0;
	}
	for(int i=0; i<q; i++) xs[a[i]] = 0;
	int k=0;
	for(auto p: xs){
		xs[p.first] = k;
		k++;
	}
	map<ll, int> ys;
	for(int i=0; i<n; i++){
		ys[y[i]] = 0;
		ys[y[i]+d[i]] = 0;
	}
	for(int i=0; i<q; i++) ys[b[i]] = 0;
	k=0;
	for(auto p: ys){
		ys[p.first] = k;
		k++;
	}

	vector<pair<pair<int, ll>, pair<int, int>>> xy(2*n);
	vector<pair<int, pair<int, int>>> ab(q);

	for(int i=0; i<n; i++){
		xy[i] = {{xs[x[i]], c[i]}, {ys[y[i]], ys[y[i]+d[i]]+1}};
		xy[i+n] = {{xs[x[i]+d[i]]+1, -c[i]}, {ys[y[i]], ys[y[i]+d[i]]+1}};
	}
	for(int i=0; i<q; i++){
		ab[i] = {xs[a[i]], {ys[b[i]], i}};
	}

	sort(xy.begin(), xy.end());
	sort(ab.begin(), ab.end());

	vector<ll> ans(q);
	LazySegmentTree<ll, ll> st(200000, 0, 0);
	int m=0, l=0;
	for(int p=0; p<200000; p++){
		if(m==xy.size()&&l==ab.size()) break;
		while(m<xy.size()&&xy[m].first.first==p){
			int ya = xy[m].second.first;
			int yb = xy[m].second.second;
			ll c = xy[m].first.second;
			st.update(ya, yb, c);
			dbg("u", xy[m].first.first, ya, yb, c);
			m++;
		}

		while(l<ab.size()&&ab[l].first==p){
			int yy=ab[l].second.first;
			int i=ab[l].second.second;
			ans[i] = st.query(yy, yy+1);
			dbg("q", ab[l].first, yy, i, ans[i]);
			l++;
		}
	}

	for(int i=0; i<q; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
