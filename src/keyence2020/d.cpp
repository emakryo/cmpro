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

int main(){
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	int ans = 1e9;
	for(int k=0; k<(1<<N); k++){

		vector<pair<int, int>> xs;
		vector<pair<int, int>> ys;
		for(int i=0; i<N; i++){
			if((k>>i)&1){
				if(i%2) xs.push_back({B[i] ,i});
				else ys.push_back({B[i], i});
			} else {
				if(i%2) ys.push_back({A[i], i});
				else xs.push_back({A[i], i});
			}
		}
		if(xs.size()!=(N+1)/2) continue;

		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		debug(k, (int)xs.size(), (int)ys.size());

		vector<pair<int, int>> zs(N);
		for(int i=0; i<N; i++) zs[i] = i%2?ys[i/2]:xs[(i+1)/2];

		bool sorted = true;
		for(int i=0; i<N-1; i++){
			if(zs[i].first>zs[i+1].first) sorted=false;
		}
		if(!sorted) continue;

		vector<int> ix(N);
		for(int i=0; i<N; i++) ix[i] = zs[i].second+1;

		ans = min(ans, crossing(ix));
	}

	cout << (ans==1e9?-1:ans) << endl;

	return 0;
}
