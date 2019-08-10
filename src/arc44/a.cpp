#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_prime(ll x){
	if(x==1) return false;
	for(int i=2; i*i<=x; i++){
		if(x%i==0) return false;
	}
	return true;
}

int main(){
	ll N;
	cin >> N;
	if(is_prime(N)){
		cout << "Prime" << endl;
	} else {
		if(N==1||N%2==0||N%10==5){
			cout << "Not Prime" << endl;
		} else {
			int dsum = 0;
			for(ll d=1; d<=1e12; d*=10){
				dsum += (N/d)%10;
			}
			if(dsum%3==0){
				cout << "Not Prime" << endl;
			} else {
				cout << "Prime" << endl;
			}
		}
	}
	return 0;
}
