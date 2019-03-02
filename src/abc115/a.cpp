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
	int d;
	cin >> d;

	cout << "Christmas";

	for(int i=0; i<25-d; i++) cout << " Eve";

	cout << endl;

	return 0;
}
