#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
const int P = 1000000007;
int N;
ll X[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i];

	vector<ll> stack;
	ll ans = 1;
	for(int i=0; i<N; i++){
		if(X[i] < 2*stack.size()+1){
			ans *= stack.size()+1;
			ans %= P;
		}
		else{
			stack.push_back(X[i]);
		}
	}

	for(int i=0; i<stack.size(); i++){
		ans *= i+1;
		ans %= P;
	}

	cout << ans << endl;

	return 0;
}
