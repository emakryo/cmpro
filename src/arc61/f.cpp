#include<iostream>
#include<stack>
using namespace std;
const int MAX = 10000000;
long N,M,K;
long fact[MAX];

long pow(long a,long n,long p){
	if(n == 0) return 1;
	if(n == 1) return a%p;
	if(n%2 == 0) {
		long t=pow(a,n/2,p);
		return (t*t)%p;
	}
	else {
		long t=pow(a,n-1,p);
		return (a*t)%p;
	}
}

long fact_nondiv(long n, long p){
	if(n == 0 || n == 1) return 1;
	long a = fact_nondiv(n/p, p);
	long b = fact[n%p];

	if(n/p%2) return a*(p-b)%p;
	else return a*b%p;
}

long fact_numdiv(long n, long p){
	long x = 0;
	while(n > 0){
		x += n/p;
		n /= p;
	}
	return x;
}

long mod_inv(long a, long m){
	int p=m,q=a%m;
	stack<int> s;
	s.push(p);
	s.push(q);
	while(q>0){
		int r = p%q;
		s.push(r);
		p = q;
		q = r;
	}
	s.pop();s.pop();
	int x=1,y=0;
	while(!s.empty()){
		q = p;
		p = s.top();
		s.pop();
		int z = x-(p/q)*y;
		x = y;
		y = z;
	}
	return (y+m)%m;
}


long comb(long n, long k, long p){
	if(n == 0 || k == 0 || n < k) return 1;
	if(fact_numdiv(n,p) > fact_numdiv(k,p) + fact_numdiv(n-k,p)){
		return 0;
	}
	else{
		return fact_nondiv(n,p)*mod_inv(fact_nondiv(k,p)*fact_nondiv(n-k,p)%p,p)%p;
	}
}

int main(){
	long p = 1000000007;
	fact[0] = 1;
	for(int i=1; i<MAX; i++){
		fact[i] = fact[i-1]*i%p;
	}
	cin >> N >> M >> K;
	long res = 0;
	long s = 1;
	for(int i=N; i<=N+M+K; i++){
		long x = comb(i-1,N-1,p);
		long y = pow(3,N+M+K-i,p);
		long z = s;
		//cout << x << " " << y << " " << z << endl;
		res = (res + (x*y%p)*z%p)%p;
		long l=0,r=0;
		if(i-N >= K) l = comb(i-N, i-N-K, p);
		if(i-N >= M) r = comb(i-N, M, p);
		//cout << l << " " <<  r << endl;
		s = (s*2-l-r+p*2)%p;
	}
	cout << res << endl;
	/*
	cin >> N >> M;
	cout << comb(N,M,p) << endl;
	*/

	return 0;
}
