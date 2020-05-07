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
	int N, K;
	cin >> N >> K;
	vector<bool> have(N);
	for(int i=0; i<K; i++){
		int d;
		cin >> d;
		for(int j=0; j<d; j++){
			int a;
			cin >> a;
			have[a-1] = true;
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		if(!have[i]) ans++;
	}
	cout << ans << endl;
	return 0;
}
