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
const ll P = 1e9+7;
int N, K;
string V;

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

struct LeftSumMax {
	int left, sum;
};
template <>
LeftSumMax SegmentTree<LeftSumMax>::merge(LeftSumMax a, LeftSumMax b){
	LeftSumMax c;
	c.left = max(a.left, a.sum+b.left);
	c.sum = a.sum+b.sum;
	return c;
}

//int _main(){
//	int a[] = {4,2,2,1,5,9,10};
//	SegmentTree<int> st(a, a+sizeof(a)/sizeof(int), 1<<20);
//	cout << st.query(0, 4) << endl;
//	for(int i=0; i<8; i++) cout << st.query(i, i+1) << endl;
//
//	return 0;
//}

ll solve(){
	cin >> N >> K;
	cin >> V;

	vector<bool> change(N);

	vector<LeftSumMax> c;
	for(int i=0; i<N; i++){
		int s = V[i]=='A'?-1:1;
		c.push_back({s, s});
	}
	//for(int i=0; i<N; i++) cout << c[i].left << (i<N-1?' ':'\n');
	SegmentTree<LeftSumMax> st(c.begin(), c.end(), {(int)-1e8, 0});
	//for(int i=0; i<N; i++) cout << st.query(i, i+1).sum << (i<N-1?' ':'\n');

	for(int i=N-1; i>=0; i--){
		if(V[i]=='A' || change[i]) continue;
		//cout << i << " " << st.query(i, N).left << endl;
		if(st.query(i, N).left > K){
			st.update(i, {-1, -1});
			change[i] = true;
		}
	}

	ll r = 2;
	ll ans = 0;
	for(int i=0; i<N; i++){
		if(change[i]){
			ans = (ans+r)%P;
		}
		r = 2*r%P;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		cout << "Case #" << i+1 << ": " << solve() << endl;
	}

	return 0;
}
