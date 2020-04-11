#include<bits/stdc++.h>
#include<cassert>
using namespace std;
typedef long long ll;

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

struct Node {
	ll sum;
	int x, y;
};

template <>
Node SegmentTree<Node>::merge(Node a, Node b){
	return a.sum < b.sum ? a : b;
}

void solve(){
	int R, C;
	cin >> R >> C;
	vector<vector<int>> S(R, vector<int>(C));

	for(int i=0; i<R; i++) for(int j=0; j<C; j++){
		cin >> S[i][j];
	}

	vector<vector<int>> up(R, vector<int>(C, -1));
	vector<vector<int>> down(R, vector<int>(C, -1));
	vector<vector<int>> left(R, vector<int>(C, -1));
	vector<vector<int>> right(R, vector<int>(C, -1));
	vector<vector<ll>> sum(R, vector<ll>(C));

	for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
		if(i>0){
			sum[i][j] += S[i][j]-S[i-1][j];
			up[i][j] = i-1;
		}
		if(i<R-1){
			sum[i][j] += S[i][j]-S[i+1][j];
			down[i][j] = i+1;
		}
		if(j>0){
			sum[i][j] += S[i][j]-S[i][j-1];
			left[i][j] = j-1;
		}
		if(j<C-1){
			sum[i][j] += S[i][j]-S[i][j+1];
			right[i][j] = j+1;
		}
	}

	vector<Node> node(R*C);
	ll score = 0;
	for(int i=0; i<R; i++) for(int j=0; j<C; j++){
		node[C*i+j].sum = sum[i][j];
		node[C*i+j].x = i;
		node[C*i+j].y = j;
		score += S[i][j];
	}

	Node def;
	def.sum = 1e18;
	SegmentTree<Node> st(node, def);

	ll ans = score;

	while(true){
		//cout << score << endl;
		vector<Node> pop;
		bool change = false;
		while(true){
			Node n = st.query(0, R*C);
			if(n.sum >= 0) break;
			pop.push_back(n);
			st.update(C*n.x+n.y, def);
		}

		for(Node &n: pop){
			change = true;
			st.update(C*n.x+n.y, def);
			//cout << n.x << " " << n.y << " " << n.sum << endl;
			score -= S[n.x][n.y];

			if(up[n.x][n.y]>=0){
				down[up[n.x][n.y]][n.y] = down[n.x][n.y];
				sum[up[n.x][n.y]][n.y] -= S[up[n.x][n.y]][n.y] - S[n.x][n.y];
				if(down[n.x][n.y]>=0){
					sum[up[n.x][n.y]][n.y] += S[up[n.x][n.y]][n.y] - S[down[n.x][n.y]][n.y];
				}

				Node m;
				m.sum = sum[up[n.x][n.y]][n.y];
				m.x = up[n.x][n.y];
				m.y = n.y;
				st.update(C*m.x+m.y, m);
			}

			if(down[n.x][n.y]>=0){
				up[down[n.x][n.y]][n.y] = up[n.x][n.y];
				sum[down[n.x][n.y]][n.y] -= S[down[n.x][n.y]][n.y] - S[n.x][n.y];
				if(up[n.x][n.y]>=0){
					sum[down[n.x][n.y]][n.y] += S[down[n.x][n.y]][n.y] - S[up[n.x][n.y]][n.y];
				}

				Node m;
				m.sum = sum[down[n.x][n.y]][n.y];
				m.x = down[n.x][n.y];
				m.y = n.y;
				st.update(C*m.x+m.y, m);
			}

			if(left[n.x][n.y]>=0){
				right[n.x][left[n.x][n.y]] = right[n.x][n.y];
				sum[n.x][left[n.x][n.y]] -= S[n.x][left[n.x][n.y]] - S[n.x][n.y];
				if(right[n.x][n.y]>=0){
					sum[n.x][left[n.x][n.y]] += S[n.x][left[n.x][n.y]]-S[n.x][right[n.x][n.y]];
				}

				Node m;
				m.sum = sum[n.x][left[n.x][n.y]];
				m.x = n.x;
				m.y = left[n.x][n.y];
				st.update(C*m.x+m.y, m);
			}

			if(right[n.x][n.y]>=0){
				left[n.x][right[n.x][n.y]] = left[n.x][n.y];
				sum[n.x][right[n.x][n.y]] -= S[n.x][right[n.x][n.y]] - S[n.x][n.y];
				if(left[n.x][n.y]>=0){
					sum[n.x][right[n.x][n.y]] += S[n.x][right[n.x][n.y]]-S[n.x][left[n.x][n.y]];
				}

				Node m;
				m.sum = sum[n.x][right[n.x][n.y]];
				m.x = n.x;
				m.y = right[n.x][n.y];
				st.update(C*m.x+m.y, m);
			}
		}
		if(change){
			ans += score;
		} else {
			break;
		}
	}

	cout << ans << endl;
}

int main(){
	int T;
	cin >> T;
	for(int t=1; t<=T; t++){
		cout << "Case #" << t << ": ";
		solve();
	}

	return 0;
}
