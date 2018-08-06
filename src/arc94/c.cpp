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
int X[3];

int main(){
	for(int i=0; i<3; i++) cin >> X[i];
	sort(X, X+3);

	int ans = 0;
	while(X[0]+2<=X[1]){
		ans += 1;
		X[0] += 2;
	}
	while(X[1]+1<=X[2]){
		ans += 1;
		X[0] += 1;
		X[1] += 1;
	}
	if(X[0]<X[1]){
		ans += 2;
	}
	cout << ans << endl;


	return 0;
}
