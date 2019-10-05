#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

template <class T>
struct SegmentTree{
	std::vector<T> v;
	T def;
	int n;
	template<class I>
	SegmentTree(I first, I last, T default_value){
		n = 1;
		def = default_value;
		while(n < last-first) n <<= 1;
		v.assign(2*n-1, default_value);
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

typedef pair<int, int> pii;
template <>
pii SegmentTree<pii>::merge(pii a, pii b){
	return {min(a.first, b.first), max(a.second, b.second)};
}

int main(){
	int N, K;
	cin >> N >> K;
	vector<int> P(N);
	for(int i=0; i<N; i++) cin >> P[i];

	vector<pii> pp(N);
	for(int i=0; i<N; i++) pp[i] = {P[i], P[i]};
	SegmentTree<pii> st(pp, {1e9, -1});

	vector<int> sorted(N-K+1);
	for(int i=0; i<K-1; i++){
		sorted[0] += P[i]<P[i+1]?1:0;
	}
	for(int i=1; i<=N-K; i++){
		sorted[i] += sorted[i-1] - (P[i-1]<P[i]?1:0) + (P[i+K-2]<P[i+K-1]?1:0);
	}

	if(N==K){
		cout << 1 << endl;
		return 0;
	}

	int ans = 0;
	int n_unchanged = 0;
	for(int i=0; i<=N-K; i++){
		if(sorted[i]==K-1){
			n_unchanged += 1;
		} else if(i==N-K){
			ans++;
		} else {
			pii p = st.query(i, i+K+1);
			debug(i, sorted[i], P[i], p.first, P[i+K], p.second);
			if(p.first != P[i] || p.second != P[i+K]){
				ans++;
			}
		}
	}
	debug(ans, n_unchanged);
	cout << ans + (n_unchanged>0?1:0)<< endl;
	return 0;
}
