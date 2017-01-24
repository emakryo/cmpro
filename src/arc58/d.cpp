#include<iostream>
#include<algorithm>
using namespace std;
const int HWmax = 1000000;
const long P = 1000000007;
int H,W,A,B;

long ext_gcd(long a, long b, long &x, long &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	else{
		long gcd = ext_gcd(b, a%b, x, y);
		return gcd;
	}
}

int main(){
	cin >> H >> W >> A >> B;

	for(int i=0; i<H+W; i++){
		if(i < H-A){
		}
		else if(i < H-A < H+B){
		}
		else{
		}
	}

	cout << endl;
	return 0;
}
