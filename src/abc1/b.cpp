#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int M;

int main(){
	cin >> M;
	cout << setw(2) << setfill('0');
	if(M < 100) cout << 0 << endl;
	else if(M <= 5000) cout << M/100 << endl;
	else if(M <= 30000) cout << M/1000+50 << endl;
	else if(M <= 70000) cout << (M-30000)/5000+80 << endl;
	else cout << 89 << endl;
	return 0;
}
