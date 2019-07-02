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
int N, M;

int main(){
	cin >> N >> M;
	int a_odd=0, b_odd=0;
	for(int i=0; i<N; i++){
		ll a;
		cin >> a;
		if(a%2) a_odd++;
	}
	for(int i=0; i<M; i++){
		ll b;
		cin >> b;
		if(b%2) b_odd++;
	}

	cout << min(a_odd, M-b_odd)+min(N-a_odd, b_odd) << endl;


	return 0;
}
