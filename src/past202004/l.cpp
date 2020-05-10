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

template <class T>
struct SegmentTree{
	std::vector<T> v;
	T def;
	int n;
	SegmentTree(int n_, T default_value): def(default_value){
		n = 1;
		while(n<n_) n <<= 1;
		v.assign(2*n-1, def);
	}
	template<class I>
	SegmentTree(I first, I last, T default_value): SegmentTree(last-first, default_value){
		copy(first, last, v.begin()+n-1);
		for(int i=n-2; i>=0; i--)
			v[i] = merge(v[2*i+1], v[2*i+2]);
	}
	SegmentTree(std::vector<T> initial_data, T default_value):
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

template <typename T>
T SegmentTree<T>::merge(T a, T b){
	return std::min(a, b);
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, k, d;
	cin >> n >> k >> d;
	vector<pair<ll, int>> a(n);

	for(int i=0; i<n; i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	if(n < 1+(k-1)*d) {
		cout << -1 << endl;
		return 0;
	}
	SegmentTree<pair<ll, int>> st(a, {1e18, 0});

	vector<ll> ans(k);
	int j=0;
	for(int i=0; i<k; i++){
		dbg(j, n-(k-i-1)*d);
		pair<ll, int> p = st.query(j, n-(k-i-1)*d);
		ans[i] = p.first;
		j = d+p.second;
	}
	cout << ans << endl;

	return 0;
}
