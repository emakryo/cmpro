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
ll A, B;

ll count(ll x){
	ll ans = 0;
	bool flag = false;
	ll base10;
	ll base8;
	for(int p=18; p>=0; p--){
		base10 = 1;
		base8 = 1;
		for(int i=0; i<p; i++){
			base10 *= 10;
			base8 *= 8;
		}
		ll digit = (x/base10)%10;
		if(x/base10 == 0) continue;
		ll y;
		if(flag){
			y = digit*base10;
		}
		else if(digit <= 4){
			y = digit*(base10-base8);
		}
		else{
			y = (digit-1)*(base10-base8) + base10;
		}
		ans += y;
		//cout << digit << " " << base10 << " " << base8 << " " << y << endl;
		if(flag || digit == 4 || digit == 9) flag=true;
	}
	if(flag) ans += 1;
	return ans;
}

int main(){
	cin >> A >> B;
	cout << count(B) - count(A-1) << endl;
	return 0;
}
