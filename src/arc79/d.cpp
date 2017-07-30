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
ll K;

int main(){
	cin >> K;

	ll k = K % 50;

	vector<ll> a(50);
	for(int i=0; i<k; i++){
		a[i] = 50-k+50;
	}
	for(int i=k; i<50; i++){
		a[i] = 49-k;
	}

	for(int i=0; i<50; i++){
		a[i] += K/50;
	}

	cout << 50 << endl;
	for(int i=0; i<50; i++){
		cout << a[i] << (i==49 ? '\n' : ' ');
	}

	return 0;
}
