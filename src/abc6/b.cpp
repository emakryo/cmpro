#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int n;
	cin >> n;
	int a=0, b=0, c=1;
	for(int i=0; i<n-1; i++){
		int na = b;
		int nb = c;
		int nc = (a+b+c)%10007;
		a = na;
		b = nb;
		c = nc;
	}
	cout << a << endl;

	return 0;
}
