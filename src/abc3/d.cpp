#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const ll P = 1000000007;
const int RCmax = 30;
ll fact[1000];
int R, C, X, Y, D, L;

ll ext_gcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	else{
		ll nx, ny;
		ll d = ext_gcd(b, a%b, nx, ny);
		x = ny;
		y = nx - (a/b) * ny;
		return d;
	}
}

ll mod_inv(ll a, ll p){
	ll x, y;
	ext_gcd(a, p, x, y);
	while(x >= p) x -= p;
	while(x < 0) x += p;
	return x;
}

ll comb(ll n, ll m, ll p){
	// p > n >= m
	if(fact[n] == 0){
		fact[0] = 1;
		for(int i=1; i<=n; i++){
			fact[i] = fact[i-1] * i % p;
		}
	}

	ll inv = mod_inv(fact[m]*fact[n-m]%p, p);
	return fact[n] * inv % p;
}

int main(){
	cin >> R >> C;
	cin >> X >> Y;
	cin >> D >> L;

	ll all = comb(X*Y, D, P) * comb(X*Y-D, L, P) % P;
	ll upper = (X-1)*Y >= D+L ? comb((X-1)*Y, D, P) * comb((X-1)*Y-D, L, P) % P : 0;
	ll left = X*(Y-1) >= D+L ? comb(X*(Y-1), D, P) * comb(X*(Y-1)-D, L, P) % P : 0;
	ll hori = (X-2)*Y >= D+L ? comb((X-2)*Y, D, P) * comb((X-2)*Y-D, L, P) % P : 0;
	ll vert = X*(Y-2) >= D+L ? comb(X*(Y-2), D, P) * comb(X*(Y-2)-D, L, P) % P : 0;
	ll upperleft = (X-1)*(Y-1) >= D+L ?
		comb((X-1)*(Y-1), D, P) * comb((X-1)*(Y-1)-D, L, P) % P : 0;
	ll vertupper = (X-1)*(Y-2) >= D+L ?
		comb((X-1)*(Y-2), D, P) * comb((X-1)*(Y-2)-D, L, P) % P : 0;
	ll horileft = (X-2)*(Y-1) >= D+L ?
		comb((X-2)*(Y-1), D, P) * comb((X-2)*(Y-1)-D, L, P) % P : 0;
	ll center = (X-2)*(Y-2) >= D+L && X > 2 ?
		comb((X-2)*(Y-2), D, P) * comb((X-2)*(Y-2)-D, L, P) % P : 0;
	/*
	cout << all << endl;
	cout << upper << endl;
	cout << left << endl;
	cout << hori << endl;
	cout << vert << endl;
	cout << upperleft << endl;
	cout << vertupper << endl;
	cout << horileft << endl;
	cout << center << endl;
	*/

	ll ans = (all - (2*upper + 2*left - hori - vert - 4*upperleft
			+ 2*vertupper + 2*horileft - center)) % P;
	while(ans < 0) ans += P;

	cout << (ans * (R-X+1) % P) * (C-Y+1) % P << endl;

	return 0;
}
