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
	int a, b, c;
	cin >> a >> b >> c;
	cout << max(0, c-(a-b)) << endl;


	return 0;
}
