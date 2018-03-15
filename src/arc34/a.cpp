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
	int N;
	double ans=0;
	cin >> N;
	for(int i=0; i<N; i++){
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		ans = max(ans, a+b+c+d+(double)e*110/900);
	}
	cout << setprecision(10) << ans << endl;

	return 0;
}
