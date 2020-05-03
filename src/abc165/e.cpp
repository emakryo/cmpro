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

int main() {
	ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;

	vector<pair<int, int>> ans;
	if(N%2){
		for(int i=0; i<N/2; i++){
			ans.push_back({i+1, N-i-1});
		}
	} else {
		set<int> diff;
		int k=0;
		for(int i=0; i<N/2-1; i++){
			while(true){
				if(diff.count(2*i+k+1)==0&&2*(N-2*i-k-1)!=N) break;
				k++;
			}
			ans.push_back({i+1, N-i-k});
			diff.insert(N-2*i-k-1);
		}
	}

	for(int i=0; i<M; i++){
		cout << ans[i].first << " " << ans[i].second << endl;
	}

	return 0;
}
