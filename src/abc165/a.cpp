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
	int K, A, B;
	cin >> K >> A >> B;
	for(int i=A; i<=B; i++){
		if(i%K==0){
			cout << "OK" << endl;
			return 0;
		}
	}
	cout << "NG" << endl;
	return 0;
}
