#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<set>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int Na, Nb;
ll A[Nmax], B[Nmax];

int main(){
	cin >> Na >> Nb;
	for(int i=0; i<Na; i++) cin >> A[i];
	for(int i=0; i<Nb; i++) cin >> B[i];

	set<ll> seta;
	for(int i=0; i<Na; i++) seta.insert(A[i]);

	int cap = 0, cup = Na;
	for(int i=0; i<Nb; i++){
		if(seta.find(B[i]) == seta.end()){
			cup += 1;
		} else {
			cap += 1;
		}
	}

	cout << setprecision(10) << (double)cap/cup << endl;

	return 0;
}
