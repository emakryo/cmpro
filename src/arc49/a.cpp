#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int A, B, C, D;
string S;
int main(){
	cin >> S;
	cin >> A >> B >> C >> D;

	string ans;
	for(int i=0; i<S.size(); i++){
		if(i==A||i==B||i==C||i==D){
			ans += '"';
		}
		ans += S[i];
	}

	if(D==S.size()) ans += '"';
	cout << ans << endl;

	return 0;
}
