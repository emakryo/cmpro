#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 777;
int N, B[10], c[10];
ll A[Nmax];

ll conv(ll x){
	ll b=1e9;
	ll y=0;
	while(b > 0){
		y += c[(x/b)%10]*b;
		b /= 10;
	}
	return y;
}

int main(){
	for(int i=0; i<10; i++) cin >> B[i];
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(B[j] == i){
				c[i] = j;
			}
		}
	}

	vector<pair<ll, ll> > vec(N);
	for(int i=0; i<N; i++) vec[i] = make_pair(conv(A[i]),A[i]);
	sort(vec.begin(), vec.end());
	for(int i=0; i<N; i++){
		cout << vec[i].second << endl;
	}

	return 0;
}
