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
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	map<ll, int> cnt;
	for(int i=0; i<N; i++){
		cnt[A[i]-i]++;
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		ans += cnt[-A[i]-i];
		cnt[A[i]-i]--;
	}

	cout << ans << endl;

	return 0;
}
