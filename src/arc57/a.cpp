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
const ll c = 2000000000000LL;

int main(){
	ll A, K;
	cin >> A >> K;

	if(K==0){
		cout << c-A << endl;
		return 0;
	}

	int n = 0;
	while(A < c){
		A += 1 + A*K;
		n++;
	}

	cout << n << endl;

	return 0;
}
