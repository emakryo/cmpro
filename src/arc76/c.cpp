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
const int Nmax = 1e5+1;
const ll P = 1000000007;

int main(){
	ll N, M;
	cin >> N >> M;

	vector<ll> fact(Nmax);
	fact[0] = fact[1] = 1;
	for(int i=2; i<Nmax; i++){
		fact[i] = (fact[i-1] * i) % P;
	}

	if(N == M){
		cout << ((2*fact[N])%P)*fact[M]%P << endl;
	}
	else if(abs(N-M)==1){
		cout << (fact[N]*fact[M])%P << endl;
	}
	else{
		cout << 0 << endl;
	}

	return 0;
}
