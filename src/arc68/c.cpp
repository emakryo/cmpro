#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	ll x;
	cin >> x;
	ll ans = 2*(x/11);
	if(x%11 >= 7) ans += 2;
	else if(x%11 > 0) ans += 1;
	cout << ans << endl;

	return 0;
}
