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

// Example

template <>
pair<int, int> SegmentTree<pair<int, int>>::merge(pair<int, int> a, pair<int, int> b){
	return std::max(a, b);
}

int main(){
	int N;
	cin >> N;
	vector<pair<int, int>> AB(N);
	for(int i=0; i<N; i++) cin >> AB[i].first;
	for(int i=0; i<N; i++) cin >> AB[i].second;
	sort(AB.begin(), AB.end());

	vector<pair<int, int>> bs(N);
	for(int i=0; i<N; i++) bs[i]={AB[i].second, -i};
	SegmentTree<pair<int, int>> st(bs, {0, 0});

	int cnt = 0;
	for(int i=N-1; i>0; i--){
		int a = AB[i].first;
		int b = AB[i].second;
		if(a<=b) continue;
		debug(a, b);
		cnt++;
		auto p = st.query(0, i);
		int x = p.first;
		int n = -p.second;
		if(x<a) {
			cout << "No" << endl;
			return 0;
		}
		p = st.query(0, 1);
		x = p.first;
		n = -p.second;
		if(x>=a){
			st.update(0, {b, 0});
			AB[n].second = b;
			continue;
		}
		int lb = 1, ub = i;
		while(ub-lb>1){
			int m = (lb+ub)/2;
			p = st.query(0, m);
			x = p.first;
			if(x>=a){
				ub = m;
			} else {
				lb = m;
			}
		}
		p = st.query(0, ub);
		n = -p.second;
		st.update(n, {b, -n});
		AB[n].second = b;
	}


	if(AB[0].first <= AB[0].second && cnt <= N-2){
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}
