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
	ll n, m, d;
	cin >> n >> m >> d;

	cout << setprecision(10);
	if(d == 0){
		cout << (double)(m-1)/n << endl;
	}
	else{
		cout << (double)(m-1)*2*(n-d)/(n*n) << endl;
	}

	return 0;
}
