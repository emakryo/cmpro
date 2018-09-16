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
int K;

double f(ll x){
	int s = 0;
	ll y = x;
	while(y>0){
		s += y%10;
		y /= 10;
	}
	return (double)x/s;
}

int main(){
	cin >> K;

	cout << 1 << endl;
	ll x = 2;
	for(int i=1; i<K; i++){
		ll z, y;
		z = y = x;
		double fmin = f(z);
		for(ll d=1; d<=x; d*=10){
			y = y + (9-(y/d)%10)*d;
			double fy = f(y);
			if(fy < fmin){
				z = y;
				fmin = fy;
			}
			//cout << y << "(" << fy << ")" << endl;
		}
		cout << z << endl;
		x = z+1;
	}

	return 0;
}
