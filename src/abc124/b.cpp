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
int N;
int H[20];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> H[i];

	int ans = 0;
	int hmax = 0;
	for(int i=0; i<N; i++){
		if(hmax <= H[i]) ans++;
		hmax = max(hmax, H[i]);
	}

	cout << ans << endl;

	return 0;
}
