#include<iostream>
using namespace std;

long gcd(long x, long y){
	if(y==0) return x;
	return gcd(y, x%y);
}

int main(){
	long g,l;
	while(cin >> g >> l){
		long ab = gcd(g, l);
		cout << a*g << " " << b*g << endl;
	}
	return 0;
}
