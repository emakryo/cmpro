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
ll A, B, C, D;

ll gcd(ll x, ll y){
	if(y==0) return x;
	return gcd(y, x%y);
}

int main(){
	cin >> A >> B >> C >> D;

	ll g = C*D/gcd(C, D);

	cout << B-A+1 - (B/C - (A-1)/C) - (B/D - (A-1)/D) + (B/g - (A-1)/g) << endl;

	return 0;
}
