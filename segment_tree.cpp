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

template <class T>
class SegmentTree{
	vector<T> v;
	T def;
	int n;
	public:
	SegmentTree(vector<T> initial_data, T default_value){
		n = 1;
		def = default_value;
		while(n < initial_data.size()) n <<= 1;
		v = vector<T>(2*n-1, default_value);
		copy(initial_data.begin(), initial_data.end(), v.begin()+n-1);
		for(int i=n-2; i>=0; i--)
			v[i] = merge(v[2*i+1], v[2*i+2]);
	}
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
	return min(a, b);
}

int main(){
	int a[] = {1,2,6,3,5,9,10};
	vector<int> v(a, a+sizeof(a));
	SegmentTree<int> st(v, 1<<30);
	cout << st.query(0, 3) << endl;
	cout << st.query(4, 7) << endl;

	return 0;
}
