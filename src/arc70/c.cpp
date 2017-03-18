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
	ll X;
	cin >> X;
	int ub=10000000, lb=0;
	while(ub-lb > 1){
		ll med = (ub+lb)/2;
		if(med*(med-1)/2 >= X){
			ub = med;
		}
		else{
			lb = med;
		}
	}

	cout << lb << endl;

	return 0;
}
