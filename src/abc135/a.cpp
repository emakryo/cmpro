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
	if((B+A)%2) cout << "IMPOSSIBLE" << endl;
	else cout << (B+A)/2 << endl;

	return 0;
}
