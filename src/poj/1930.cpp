#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<sstream>
using namespace std;
typedef long long ll;

ll gcd(ll n, ll m){
	if(m == 0) return n;
	return gcd(m, n%m);
}

int main(){
	string s;
	while(cin >> s){
		if(s == "0") break;
		ll frac;
		stringstream ss(s.substr(2, s.size()-5));
		ss >> frac;
		ll base = 1;
		for(int i=0; i<s.size()-5; i++) base *= 10;
		ll dom = 0;
		ll denom = 1e18;
		for(ll b=10; b<=base; b*= 10){
			ll dom_b = frac - frac/b;
			ll denom_b = base - base/b;
			ll g = gcd(dom_b, denom_b);
			dom_b /= g;
			denom_b /= g;
			//cout << dom_b << "/" << denom_b << endl;
			if(denom > denom_b || denom == 1e18){
				denom = denom_b;
				dom = dom_b;
			}
		}
		cout << dom << "/" << denom << endl;
	}

	return 0;
}
