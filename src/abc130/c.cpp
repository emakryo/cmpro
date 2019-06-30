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
ll W, H, X, Y;

int main(){
	cin >> W >> H >> X >> Y;

	cout << W*H/2.0 << ' ' << (2*X==W && 2*Y==H ?1:0) << endl;

	return 0;
}
