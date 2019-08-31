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
int L, N;

int main(){
	cin >> N >> L;

	if(L+N-1<0){
		cout << (N-1)*(2*L+N-2)/2 << endl;
	} else if(L<0){
		cout << N*(2*L+N-1)/2 << endl;
	} else {
		cout << (N-1)*(2*L+N)/2 << endl;
	}

	return 0;
}
