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

int main(){
	int M,N,X;
	cin >> M >> N >> X;

	int ans = X;
	int cur = X;
	while(cur >= M){
		ans += cur/M*N;
		cur = cur - (cur/M)*M + cur/M*N;
	}

	cout << ans << endl;

	return 0;
}
