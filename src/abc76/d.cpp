#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

template <class T>
struct SegmentTree{
	std::vector<T> v;
	T def;
	int n;
	SegmentTree(int n_, T default_value): def(default_value) {
		n = 1;
		while(n < n_) n <<= 1;
		v.assign(2*n-1, default_value);
	}
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
int SegmentTree<int>::merge(int a, int b){
	return std::min(a, b);
}

int main(){
	cout << setprecision(20);
	int N;
	cin >> N;
	vector<int> T(N+2), V(N+2);
	for(int i=0; i<N; i++) cin >> T[i+1];
	for(int i=0; i<N; i++) cin >> V[i+1];

	SegmentTree<int> st1(N+2, 1e9), st2(N+2, 1e9);
	int tsum = 0;
	for(int i=0; i<=N; i++){
		tsum += T[i];
		st1.update(i, V[i]-tsum);
		st2.update(i, V[i+1]+tsum);
	}

	double ans = 0;
	tsum = 0;
	for(int i=1; i<=N; i++){
		int v0 = tsum+st1.query(0, i);
		int v1 = -tsum-T[i]+st2.query(i, N+1);
		int t = T[i];
		tsum += T[i];
		debug(any{i, t, V[i], v0, v1});
		if(v0 < V[i] && v1 < V[i]){
			if(V[i]-v0 + V[i]-v1 < t){
				ans += (v0+V[i])*(V[i]-v0)*0.5 + (t-(2*V[i]-v0-v1))*V[i] + (v1+V[i])*(V[i]-v1)*0.5;
			} else if(v0+t<=v1) {
				ans += (2*v0+t) * t * 0.5;
			} else if(v1+t<=v0) {
				ans += (2*v1+t) * t * 0.5;
			} else {
				double v = 0.5 * (v1 + v0 + t);
				ans += (v0+v) * (v-v0) * 0.5 + (v1+v) * (v-v1) * 0.5;
			}
		} else if(v0 < V[i]){
			if(v0+t<=V[i]) {
				ans += (2*v0+t) * t * 0.5;
			} else {
				ans += (v0+V[i])*(V[i]-v0)*0.5 + V[i]*(t-V[i]+v0);
			}
		} else if(v1 < V[i]){
			if(v1+t<=V[i]) {
				ans += (2*v1+t) * t * 0.5;
			} else {
				ans += (v1+V[i])*(V[i]-v1)*0.5 + V[i]*(t-V[i]+v1);
			}
		} else {
			ans += t * V[i];
		}
		debug(any{ans});
	}

	cout << setprecision(20) << ans << endl;


	return 0;
}
