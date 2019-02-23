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
	int a, b;
	cin >> a >> b;
	if(b % a == 0) cout << a+b << endl;
	else cout << b-a << endl;

	return 0;
}
