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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
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
	return std::min(a, b);
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
	cout << setprecision(20) << fixed;

	int n, q; cin >> n >> q;
	vector<int> a(n), b(n), c(q), d(q);
	for(int i=0; i<n; i++) cin >> a[i] >> b[i];
	for(int i=0; i<q; i++) cin >> c[i] >> d[i];

	const int Mmax = 2e5+1;
	vector<priority_queue<pair<int, int>>> ques(Mmax);
	vector<set<int>> belong(Mmax);

	for(int i=0; i<n; i++){
		ques[b[i]].push({a[i], i});
		belong[b[i]].insert(i);
	}

	SegmentTree<int> st(Mmax, 1e9+5);
	for(int i=0; i<Mmax; i++){
		if(belong[i].size()>0) st.update(i, ques[i].top().first);
	}

	for(int i=0; i<q; i++){
		c[i]--;
		belong[b[c[i]]].erase(c[i]);
		while(ques[b[c[i]]].size()>0&&belong[b[c[i]]].count(ques[b[c[i]]].top().second)==0) ques[b[c[i]]].pop();

		if(belong[b[c[i]]].size()){
			st.update(b[c[i]], ques[b[c[i]]].top().first);
		} else{
			st.update(b[c[i]], 1e9+5);
		}

		b[c[i]] = d[i];

		belong[b[c[i]]].insert(c[i]);
		ques[b[c[i]]].push({a[c[i]], c[i]});

		st.update(b[c[i]], ques[b[c[i]]].top().first);

		cout << st.query(0, Mmax) << endl;
	}

	return 0;
}
