#include<iostream>
using namespace std;

long gcd(long x, long y){
	if(y == 0) return x;
	return gcd(y, x%y);
}

int main(){
	long a,b;
	while(cin >> a >> b){
		long g = gcd(a,b);
		cout << g << " " << (a/g)*b << endl;
	}
	return 0;
}
