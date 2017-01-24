#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const ll P = 1777777777;
ll N,K;
ll fact[1000000];

void ext_gcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return;
	}
	ll nx, ny;
	ext_gcd(b, a%b, nx, ny);
	x = ny;
	y = (nx - a/b*ny)%P;
	while(y < 0) y += P;
}

ll inv(ll x){
	ll y,z;
	ext_gcd(x, P, y, z);
	return y;
}

int main(){
	string ns;
	cin >> ns >> K;
	N = 0;
	for(int i=0; i<ns.size(); i++){
		N *= 10;
		N += ns[i]-'0';
		N %= P;
	}

	fact[0] = fact[1] = 1;
	for(ll i=2; i<1000000; i++){
		fact[i] = fact[i-1]*i%P;
	}

	ll c = 1;
	for(ll i=0; i<K; i++){
		c = c*((N-i+P)%P)%P;
	}
	for(ll i=1; i<=K; i++){
		c = c*inv(i)%P;
	}
	//cout << N << " " << K << " " << c << endl;
	ll d = 0;
	for(ll i=2; i<=K; i++){
		ll f = fact[K]*inv(fact[K-i]*fact[i]%P)%P;
		ll e = f*fact[K-i]%P;
		if(i%2==0){
			d = (d+e)%P;
		}
		else{
			d = (d-e+P)%P;
		}
	}

	cout << c*d%P << endl;

	return 0;
}
