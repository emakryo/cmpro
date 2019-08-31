#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 1e5;
ll L[Nmax];
const ll P = 1e9+7;

ll gcd(ll x, ll y){
	if(y==0) return x;
	else return gcd(y, x%y);
}

ll pow(ll x, ll y){
	if(y==0) return 1;
	if(y%2) return x*pow(x, y-1)%P;
	ll t = pow(x, y/2);
	return t*t%P;
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> L[i];

	ll lmin = L[0];
	for(int i=1; i<N; i++) lmin = min(lmin, L[i]);

	for(int i=0; i<N; i++) L[i]-=lmin;

	vector<ll> positive;
	for(int i=0; i<N; i++){
		if(L[i]>0) positive.push_back(L[i]);
	}

	ll d = 0;
	if(positive.size()>=1){
		d = positive[0];
		for(int i=1; i<positive.size(); i++){
			d = gcd(positive[i], d);
		}
	}

	//cout << lmin << " " << d << endl;
	ll ans = pow(2ll, (ll)lmin+(d+1)/2);
	cout << ans << endl;
	return 0;
}
