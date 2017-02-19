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
	ll N,M;
	cin >> N >> M;

	ll ans = 0;
	if(N <= M/2){
		ans += N;
		M -= 2*N;
		ans += M/4;
	}
	else{
		ans += M/2;
	}

	cout << ans << endl;


	return 0;
}
