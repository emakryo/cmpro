#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
string S;

int main(){
	cin >> S;
	
	ll n = S.size();
	ll ans = n*(n-1);
	for(int i=0; i<n; i++){
		if(S[i] == 'U'){
			ans += i;
		}
		else{
			ans += n-i-1;
		}
	}

	cout << ans << endl;

	return 0;
}
