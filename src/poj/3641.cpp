#include<iostream>
#include<algorithm>
using namespace std;
int prime[100000];

bool is_prime(long long x){
	if(x==0||x==1) return false;
	for(int i=2; i*i<=x; i++){
		if(x%i==0) return false;
	}
	return true;
}

long long pow(long long x, long long y, long long r){
	if(y == 0) return 1;
	else if(y == 1) return x%r;
	else if(y%2 == 0){
		long long t = pow(x, y/2, r);
		return (t*t)%r;
	}
	else{
		long long t = pow(x, y-1, r);
		return (x*t)%r;
	}
}

int main(){
	while(true){
		long long p, a;
		cin >> p >> a;
		if(p == 0 && a == 0) break;

		if(pow(a,p,p) == a%p && !is_prime(p)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}
