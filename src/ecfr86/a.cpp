#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll X, Y;
    cin >> X >> Y;
    ll A, B;
    cin >> A >> B;
    cout << abs(X-Y)*A + min(2*A, B)*min(X, Y) << endl;
}

int main() {
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        solve();
    }
	return 0;
}
