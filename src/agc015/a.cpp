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
	ll N, A, B;
	cin >> N >> A >> B;
	
	if(A > B){
		cout << 0 << endl;
		return 0;
	}
	if(N == 1 && A != B){
		cout << 0 << endl;
		return 0;
	}
	cout << (N-2)*B-(N-2)*A+1 << endl;

	return 0;
}
