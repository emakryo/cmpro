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

void solve(){
	ll A, B, N;
	string r;
	cin >> A >> B;
	cin >> N;
	ll lb=A, ub=B;
	for(int i=0; i<N; i++){
		cout << (lb+ub+1)/2 << endl;
		cin >> r;
		if(r == "CORRECT") return;
		if(r == "TOO_SMALL"){
			lb = (lb+ub+1)/2;
		}
		else if(r == "TOO_BIG"){
			ub = (lb+ub+1)/2;
		}
		else {
			return;
		}
	}
}



int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++) solve();

	return 0;
}
