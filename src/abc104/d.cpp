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
const ll P = 1e9+7;

int main(){
	string S;
	cin >> S;
	int N = S.size();

	vector<ll> n_all(N+1), n_a(N+1), n_ab(N+1), n_abc(N+1);
	n_all[0] = 1;
	for(int i=0; i<N; i++){
		n_all[i+1] = n_all[i];
		n_a[i+1] = n_a[i];
		n_ab[i+1] = n_ab[i];
		n_abc[i+1] = n_abc[i];
		if(S[i]=='A'){
			n_a[i+1] += n_all[i];
		} else if(S[i]=='B'){
			n_ab[i+1] += n_a[i];
		} else if(S[i]=='C'){
			n_abc[i+1] += n_ab[i];
		} else if(S[i]=='?'){
			n_all[i+1] = 3*n_all[i];
			n_a[i+1] = 3*n_a[i]+n_all[i];
			n_ab[i+1] = 3*n_ab[i]+n_a[i];
			n_abc[i+1] = 3*n_abc[i]+n_ab[i];
		}
		n_all[i+1] %= P;
		n_a[i+1] %= P;
		n_ab[i+1] %= P;
		n_abc[i+1] %= P;
		//cout << S[i] << " " << n_all[i+1] << " " << n_a[i+1] << " " << n_ab[i+1] << " " << n_abc[i+1] << endl;
	}

	cout << n_abc[N] << endl;

	return 0;
}
