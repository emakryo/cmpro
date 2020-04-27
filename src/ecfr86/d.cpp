#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DBG
#define dbg(...) printf(__VA_ARGS__);
#else
#define dbg(...)
#endif
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

typedef pair<int, int> pii;
template <>
pii SegmentTree<pii>::merge(pii a, pii b){
	return std::min(a, b);
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> M(N);
    for(int i=0; i<N; i++) cin >> M[i];
    vector<int> C(K);
    for(int i=0; i<K; i++) cin >> C[i];

    sort(M.rbegin(), M.rend());
    vector<pii> v(N);
    for(int i=0; i<N; i++) v[i] = {1e9, i};
    SegmentTree<pii> st(v, {1e9, 1e9});
    vector<vector<int>> ans(1, vector<int>{M[0]});
    st.update(0, {1, 0});
    for(int i=1; i<N; i++){
        pii p = st.query(0, N);
        if(p.first>=C[M[i]-1]){
            ans.push_back(vector<int>{M[i]});
            st.update(ans.size()-1, {1, ans.size()-1});
        } else {
            ans[p.second].push_back(M[i]);
            st.update(p.second, {1+p.first, p.second});
        }
    }
    cout << ans.size() << endl;
    for(int i=0; i<ans.size(); i++){
        cout << ans[i].size() << " ";
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j] << (j==ans[i].size()-1?'\n':' ');
        }
    }
	return 0;
}
