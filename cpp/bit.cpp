#include<bits/stdc++.h>

template <class T>
struct Bit{
	std::vector<T> v;
	int n;
	Bit(int n_): n(n_){ v.assign(n_, 0); }
	// i must be 0 <= i < n
	T sum(int i){
		T s=0;
		while(i>0){ s += v[i]; i -= i & -i; }
		return s;
	}
	// i must be 1 <= i < n
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

int _main(){
	using namespace std;
	Bit<int> bit(10);
	bit.add(1,10);
	bit.add(5,20);
	assert(bit.sum(0)==0);
	assert(bit.sum(2)==10);
	assert(bit.sum(5)==30);
	assert(bit.sum(8)==30);

	vector<int> v = {3, 5, 1, 2, 4};
	assert(crossing(v)==5);
	return 0;
}
