#include<bits/stdc++.h>

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
int SegmentTree<int>::merge(int a, int b){
	return std::min(a, b);
}

int main(){
	using namespace std;
	vector<int> a = {4,2,2,1,5,9,10};
	SegmentTree<int> st(a.begin(), a.end(), 1<<20);
	assert((st.query(0, 4)==1));
	for(int i=0; i<10; i++){
		assert((st.query(i, i+1)==i<a.size()?a[i]:1<<20));
	}

	return 0;
}
