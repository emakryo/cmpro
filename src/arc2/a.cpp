#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int y;
	cin >> y;
	if(y%400==0) cout << "YES" << endl;
	else if(y%100==0) cout << "NO" << endl;
	else if(y%4==0) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
