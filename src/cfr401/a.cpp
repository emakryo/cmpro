#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
ll N;
int X;

int main(){
	cin >> N >> X;

	N %= 6;

	if(N%2 == 1){
		N -= 1;
		if(X == 0) X = 1;
		else if(X == 1) X = 0;
	}
	for(int i=0; i<N; i++){
		if(i%2 == 0){
			if(X==1) X=2;
			else if(X==2) X=1;
		}
		else{
			if(X==0) X=1;
			else if(X==1) X=0;
		}
	}

	cout << X << endl;

	return 0;
}
