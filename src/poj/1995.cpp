#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll A[45000], B[45000];

ll pow(ll x, ll y, ll r){
	if(y==0) return 1;
	if(y==1) return x;
	if(y%2==0){
		ll t=pow(x,y/2,r);
		return (t*t)%r;
	}
	return (x*pow(x,y-1,r))%r;
}

int main(){
	int Z;
	cin >> Z;
	for(int i=0; i<Z; i++){
		int M,H;
		cin >> M >> H;
		for(int j=0; j<H; j++){
			cin >> A[j] >> B[j];
		}

		ll ans = 0;
		for(int j=0; j<H; j++){
			ans = (ans + pow(A[j],B[j],M))%M;
		}

		cout << ans << endl;
	}

	return 0;
}
