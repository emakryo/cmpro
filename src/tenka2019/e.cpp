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
const int Nmax=1e4+10;
ll A[Nmax];

ll gcd(ll x, ll y){
	if(y==0) return x;
	return gcd(y, x%y);
}

int main(){
	cin >> N;
	for(int i=0; i<=N; i++) cin >> A[i];

	vector<bool> is_prime(N+1, true);
	is_prime[0] = is_prime[1] = false;
	for(int p=2; p*p<=N; p++){
		if(!is_prime[p]) continue;
		for(int j=2; p*j<=N; j++) is_prime[p*j]=false;
	}
	vector<int> primes;
	primes.push_back(2);
	for(int p=3; p<=N; p+=2){
		if(is_prime[p]){
			primes.push_back(p);
		}
	}

	ll g=abs(A[N]);
	for(int i=0; i<N; i++){
		g = gcd(g, abs(A[i]));
	}
	//cout << g << endl;

	vector<int> factor;
	for(int p=2; p*p<=g; p++){
		while(g%p==0){
			factor.push_back(p);
			g /= p;
		}
	}
	if(g>1) factor.push_back(g);

	vector<ll> x(N+1);
	for(int k=0; k<primes.size(); k++){
		int p = primes[k];
		for(int i=0; i<=N; i++) x[i] = A[i]%p;
		for(int i=0; i<=N-p; i++){
			x[i+p-1] = (x[i+p-1]+x[i])%p;
			x[i] = 0;
		}
		bool f=true;
		for(int i=0; i<=N; i++) f = f&&(x[i]==0);
		//cout << p << endl;
		//for(int i=0; i<=N; i++) cout << x[i] << (i==N?'\n':' ');
		if(f) factor.push_back(p);
	}

	sort(factor.begin(), factor.end());
	auto end = unique(factor.begin(), factor.end());
	for(auto i=factor.begin(); i!=end; i++){
		cout << *i << endl;
	}


	return 0;
}
