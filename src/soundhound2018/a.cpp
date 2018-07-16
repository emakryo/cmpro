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
	if(a+b==15) cout << "+" <<endl;
	else if(a*b==15) cout << "*" << endl;
	else cout << "x" << endl;


	return 0;
}
