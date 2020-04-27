#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    string S;
    cin >> S;
    int c0 = 0;
    for(int i=0; i<S.size(); i++){
        if(S[i]=='0') c0++;
    }
    if(c0==0||c0==S.size()){
        cout << S << endl;
    }
    else{
        string ans;
        for(int i=0; i<S.size(); i++){
            ans += "01";
        }
        cout << ans << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        solve();
    }
	return 0;
}
