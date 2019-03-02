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
	int x, y, z;
	cin >> x >> y >> z;
	if(x>y&&x>z) cout << y*z/2 << endl;
	else if(y>x&&y>z) cout << x*z/2 << endl;
	else cout << x*y/2 << endl;

	return 0;
}
