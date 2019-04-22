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
const int Xmax = 1000;
int X, Y, Z, K;
ll A[Xmax], B[Xmax], C[Xmax];

int main(){
	cin >> X >> Y >> Z >> K;
	for(int i=0; i<X; i++) cin >> A[i];
	for(int i=0; i<Y; i++) cin >> B[i];
	for(int i=0; i<Z; i++) cin >> C[i];

	vector<ll> ab;
	for(int i=0; i<X; i++){
		for(int j=0; j<Y; j++){
			ab.push_back(A[i]+B[j]);
		}
	}
	sort(ab.begin(), ab.end());
	reverse(ab.begin(), ab.end());
	ab.resize(K);
	vector<ll> abc;
	for(int i=0; i<ab.size(); i++){
		for(int j=0; j<Z; j++){
			abc.push_back(ab[i]+C[j]);
		}
	}
	sort(abc.begin(), abc.end());
	reverse(abc.begin(), abc.end());
	for(int i=0; i<K; i++){
		cout << abc[i] << endl;
	}

	return 0;
}
