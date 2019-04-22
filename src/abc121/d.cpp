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

int main(){
	ll A, B;
	cin >> A >> B;

	ll ans = 0;
	if(A&1){
		if((B-A)%4==0||(B-A)%4==1){
			ans++;
		}
	} else {
		if((B-A)%4==1||(B-A)%4==2){
			ans++;
		}
	}

	for(int k=1; k<60; k++){
		ll n=0;
		if(1&(A>>k)){
			n += (1L<<(k+1))-(A&((1L<<(k+1))-1));
			//cout << k << "A" << (1L<<(k+1)) << " " << (A&((1L<<(k+1))-1)) << endl;
		}
		if(1&(B>>k)){
			n += (B&((1L<<(k+1))-1))-((1L<<k)-1);
			//cout << k << "B" << n << endl;
		}

		if(n%2){
			ans += 1L<<k;
		}
	}

	cout << ans << endl;


	return 0;
}
