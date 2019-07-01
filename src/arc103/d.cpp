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
int N;
const int Nmax = 1000;
int X[Nmax], Y[Nmax];

int main(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> X[i] >> Y[i];

	vector<ll> p(N), q(N);
	int parity = (X[0]+Y[0]+(1LL<<40))%2;
	for(int i=0; i<N; i++){
		p[i] = X[i] + Y[i];
		q[i] = X[i] - Y[i];
		if((p[i]+(1LL<<40))%2!=parity){
			cout << -1 << endl;
			return 0;
		}
		p[i] += parity-1;
		q[i] += parity-1;
	}

	cout << 40-parity << endl;
	if(parity==0){
		cout << 1 << ' ';
	}
	for(int i=0; i<39; i++) cout << (1LL<<(38-i)) << (i<38?' ':'\n');

	for(int i=0; i<N; i++){
		string ms;
		if(parity==0){
			ms += 'R';
		}

		ll k = 1LL<<38;
		ll x=0, y=0;
		if(parity==0){
			x = 1;
			y = 0;
		}
		while(k>0){
			if(p[i]>0&&q[i]>0){
				ms += 'R';
				p[i] -= k;
				q[i] -= k;
				x += k;
			} else if(p[i]<0&&q[i]<0){
				ms += 'L';
				p[i] += k;
				q[i] += k;
				x -= k;
			} else if(p[i]>0&&q[i]<0){
				ms += 'U';
				p[i] -= k;
				q[i] += k;
				y += k;
			} else{
				ms += 'D';
				p[i] += k;
				q[i] -= k;
				y -= k;
			}
			k = k>>1;
		}
		cout << ms << endl;
		//cout << x << " " << y << endl;
	}

    return 0;
}
