#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
const ll P = 1e9+7;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N, M;
	cin >> N >> M;
	vector<int> A(N);
	vector<int> B(M);
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<M; i++) cin >> B[i];

	set<int> am, bm;
	for(int i=0; i<N; i++){
		if(am.count(A[i])){
			cout << 0 << endl;
			return 0;
		}
		am.insert(A[i]);
	}
	for(int i=0; i<M; i++){
		if(bm.count(B[i])){
			cout << 0 << endl;
			return 0;
		}
		bm.insert(B[i]);
	}
	int n_done = 0, m_done = 0;
	ll ans = 1;

	for(int i=N*M; i>0; i--){
		if(am.count(i)>0&&bm.count(i)>0){
			if(n_done==N||m_done==M){
				ans = 0;
			} else {
				n_done++;
				m_done++;
			}
		} else if(am.count(i)>0){
			if(n_done==N){
				ans = 0;
			} else {
				ans *= m_done;
				ans %= P;
				n_done++;
			}
		} else if(bm.count(i)>0){
			if(m_done==M){
				ans = 0;
			} else {
				ans *= n_done;
				ans %= P;
				m_done++;
			}
		} else {
			ans *= (n_done*m_done-(N*M-i));
			ans %= P;
		}
		debug(any{i, ans, n_done, m_done});
	}

	cout << ans << endl;

	return 0;
}
