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

template <typename T>
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
	return std::max(a, b);
}

int _main(){
	using namespace std;
	vector<int> a = {4,2,2,1,5,9,10};
	SegmentTree<int> st(a.begin(), a.end(), 1<<20);
	assert((st.query(0, 4)==1));
	for(int i=0; i<10; i++){
		assert((st.query(i, i+1)==i<a.size()?a[i]:1<<20));
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> h(n);
	for(int i=0; i<n; i++) cin >> h[i];

	map<int, int> idx;
	SegmentTree<int> st(h, 0);

	vector<int> ans(n);
	cout << 0 << endl;
	for(int i=0; i<n-1; i++){
		if(i==0||st.query(0, i)<h[i]){
			cout << 1 << endl;
			ans[i] = 1;
			continue;
		}
		if(h[i-1]>h[i]){
			ans[i] = ans[i-1]+1;
			cout << ans[i] << endl;
			continue;
		}
		int lb = 0, ub = i-1;
		while(ub-lb>1){
			int m = (lb+ub)/2;
			if(st.query(m, i)<h[i]){
				ub = m;
			} else {
				lb = m;
			}
		}
		ans[i] = ans[lb]+1;
		dbg(i, h[i], h[lb]);
		cout << ans[i] << endl;
	}

	return 0;
}
