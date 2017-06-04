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

int main(){
	ll A, B;
	cin >> A >> B;

	int i=62;
	while(i >= 0 && ((A&(1L<<i)) == (B&(1L<<i)))) i--;
	if (i < 0){
		cout << 1 << endl;
		return 0;
	}

	A &= (1L<<i)-1;
	B &= (1L<<i)-1;

	int j=i-1;
	while(j >= 0 && ((B&(1L<<j)) == 0)) j--;
	//cout << i << " " << j << " " << (1L<<i) << endl;

	if((1L<<(j+1))-1 >= A){
		cout << (1L<<(i+1))-1-A+1 << endl;
		return 0;
	}
	//cout << (1L<<(j+1)) << " " <<  2*((1L<<(i))-A) << endl;
	cout << (1L<<(j+1)) + 2*((1L<<(i))-A) << endl;

	return 0;
}
