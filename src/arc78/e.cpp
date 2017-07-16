#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<string>
using namespace std;
typedef long long ll;
ll N = 1000;

bool query(ll x){
	char c;
	cout << "? " << x << endl << flush;
	cin >> c;
	return c == 'Y';

	/*
	string xs = to_string(x);
	string ns = to_string(N);
	return (x <= N && xs <= ns) || (x > N && xs > ns);
	*/
}

int main(){
	int ndigit = -1;
	ll x = 1;
	for(int i=0; i<11; i++){
		if(!query(x)){
			ndigit = i;
			break;
		}
		x *= 10;
	}

	if(ndigit < 0){
		x = 1;
		for(int i=0; i<11; i++){
			if(query(2*x)){
				ndigit = i+1;
				cout << "! " << x << endl;
				return 0;
			}
			x *= 10;
		}
	}

	x = 1;
	for(int i=1; i<ndigit; i++){
		x *= 10;
	}
	ll ub = 10*x-1;
	ll lb = x;

	for(int i=0; i<30 && ub-lb>1; i++){
		ll m = (lb+ub)/2;
		if(query(10*m)){
			ub = m;
		}
		else{
			lb = m;
		}
	}

	cout << "! " << ub << endl << flush;

	return 0;
}
