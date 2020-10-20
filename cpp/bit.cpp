#include<bits/stdc++.h>

template <typename T>
struct Bit{
	std::vector<T> v;
	int n;
	Bit(int n_): n(n_){ v.assign(n_, 0); }
	// 0 <= i < n
	T sum(int i){
		T s=0;
		while(i>0){ s += v[i]; i -= i & -i; }
		return s;
	}
	// 1 <= i < n
	void add(int i, T x){
		while(i < n){ v[i] += x; i += i & -i; }
	}
};

// v: permutation of (1, ... , n)
int crossing(std::vector<int> &v){
	Bit<int> bit(v.size()+1);
	int count = 0;
	for(int i=0; i<v.size(); i++){
		count += i - bit.sum(v[i]);
		bit.add(v[i], 1);
	}
	return count;
}
