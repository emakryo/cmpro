#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 3650;

int main(){
	vector<int> ans(6,0);

	int N;
	cin >> N;
	for(int i=0; i<N; i++){
		double H, L;
		cin >> H >> L;
		if(H >= 35) ans[0]++;
		else if(H >= 30) ans[1]++;
		else if(H >= 25) ans[2]++;
		if(L >= 25) ans[3]++;
		if(L < 0 && H >= 0) ans[4]++;
		if(H < 0) ans[5]++;
	}

	cout << ans[0];
	for(int i=1; i<6; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
