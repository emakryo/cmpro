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
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
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

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int i=0; i<n; i++){
		cin >> a[i];
	}

	dbg("pohe");

	Bit<int> bit(n+2);
	for(int i=0; i<n; i++){
		bit.add(i+1, a[i]);
		bit.add(i+2, -a[i]);
	}
	for(int j=0; j<k; j++){
		Bit<int> next(n+2);
		for(int i=0; i<n; i++){
			int b = bit.sum(i+1);
			dbg(j, i, b, max(0, i-b), min(n, i+b+1)+1, 1);
			next.add(max(0, i-b)+1, 1);
			next.add(min(n, i+b+1)+1, -1);
		}
		bit = next;
		int xmin = n;
		for(int i=0; i<n; i++){
			xmin = min(xmin, bit.sum(i+1));
		}

		if(xmin==n) break;
	}


	vector<int> ans(n);
	for(int i=0; i<n; i++){
		ans[i] = bit.sum(i+1);
	}
	cout << ans << endl;

	return 0;
}
