#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<set>
using namespace std;
typedef long long ll;

int main(){
	int s;
	cin >> s;

	set<ll> xs;
	xs.insert(s);
	ll a = s;
	int ans = 1;
	while(true){
		ans++;
		ll b;
		if(a%2==0) b = a/2;
		else b = 3*a+1;
		if(xs.find(b)!=xs.end()) break;
		xs.insert(b);
		a = b;
	}
	
	cout << ans << endl;

	return 0;
}
