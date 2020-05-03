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
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<int> A(Q), B(Q), C(Q), D(Q);
	for(int i=0; i<Q; i++){
		cin >> A[i] >> B[i] >> C[i] >> D[i];
		A[i]--; 
		B[i]--;
	}

	int ans = 0;
	vector<int> a(N, 1);
	while(true){
		int x = 0;
		dbg(a[0], a[1], a[2]);
		for(int i=0; i<Q; i++){
			if(a[B[i]]-a[A[i]]==C[i]) x += D[i];
		}
		ans = max(ans, x);

		if(a[0]==M) break;
		int i=0;
		while(i<N&&a[i]!=M) i++;
		i--;
		a[i]++;
		int b = a[i];
		i++;
		while(i<N) {
			a[i]=b;
			i++;
		}
	}

	cout << ans << endl;


	return 0;
}
