#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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

template <class T>
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

template <>
int SegmentTree<int>::merge(int a, int b){
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
typedef vector<vector<int>> Gr;

void dfs(int u, int p, Gr &graph, SegmentTree<int> &st, vector<int> &a, vector<int> &ans){
	int backup = st.query(a[u], a[u]+1);
	int x = st.query(0, a[u]);
	st.update(a[u], x+1);
	ans[u] = st.query(0, st.n);
	for(int v: graph[u]){
		if(v==p) continue;
		dfs(v, u, graph, st, a, ans);
	}
	st.update(a[u], backup);
}


int main() {
	ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N);
	for(int i=0; i<N; i++){
		cin >> A[i];
	}
	vector<vector<int>> graph(N);
	for(int i=0; i<N-1; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	vector<int> as(A);
	sort(as.begin(), as.end());
	auto e = unique(as.begin(), as.end());
	for(int i=0; i<N; i++){
		A[i] = lower_bound(as.begin(), e, A[i])-as.begin()+1;
		dbg(i, A[i]);
	}

	SegmentTree<int> st(200010, 0);

	vector<int> ans(N);
	dfs(0, -1, graph, st, A, ans);

	for(int i=0; i<N; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
