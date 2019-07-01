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
const int Nmax=50;
const ll P=1e9L+7;
ll A, B;
ll X[Nmax];


ll pow(ll x, ll n){
	if(n==0) return 1;
	if(n==1) return x%P;
	if(n%2) return x*pow(x, n-1)%P;
	ll t = pow(x, n/2);
	return t*t%P;
}

int main(){
	cin >> N >> A >> B;
	for(int i=0; i<N; i++) cin >> X[i];
	if(N==1){
		cout << pow(A, B)*X[0]%P << endl;
		return 0;
	}
	if(A==1){
		sort(X, X+N);
		for(int i=0; i<N; i++) cout << X[i]%P << endl;
		return 0;
	}

	priority_queue<pair<double, pair<ll, ll> >,
		vector<pair<double, pair<ll, ll> > >,
		greater<pair<double, pair<ll, ll> > > > logA;
	double logA_max = 0;
	for(int i=0; i<N; i++){
		double a = log(X[i]) / log(A);
		logA.push(make_pair(a, make_pair(0, X[i])));
		logA_max = max(logA_max, a);
	}
	while(B > 0 && logA_max - logA.top().first > 1){
		pair<double, pair<ll, ll> > t = logA.top();
		logA.pop();
		ll a = logA.top().first - t.first + 1;
		a = min(B, a);
		B -= a;
		//cout << t.first << " " << logA_max << endl;
		t.first += a;
		t.second.first += a;
		logA.push(t);
		logA_max = max(logA_max, t.first);
	}

	/*
	auto tmp = logA;
	for(int i=0; i<N; i++){
		pair<double, pair<ll, ll> > t = logA.top();
		logA.pop();
		cout << t.first << " " << t.second.first << " " << t.second.second << endl;
	}
	logA = tmp;
	*/

	for(int i=0; i<N; i++){
		pair<double, pair<ll, ll> > t = logA.top();
		logA.pop();
		t.first += B/N;
		t.second.first += B/N;
		logA.push(t);
	}
	for(int i=0; i<B%N; i++){
		pair<double, pair<ll, ll> > t = logA.top();
		logA.pop();
		t.first += 1;
		t.second.first += 1;
		logA.push(t);
	}

	for(int i=0; i<N; i++){
		pair<double, pair<ll, ll> > t = logA.top();
		logA.pop();
		cout << pow(A, t.second.first)*t.second.second%P << endl;
	}

	return 0;
}
