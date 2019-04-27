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
const int Nmax = 1e5;
int N;
ll A[Nmax];

ll gcd(ll x, ll y){
	if(y==0) return x;
	else return gcd(y, x%y);
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> front, end;
	front.push_back(A[0]);
	for(int i=1; i<N; i++) front.push_back(gcd(front.back(), A[i]));
	end.push_back(A[N-1]);
	for(int i=N-2; i>=0; i--) end.push_back(gcd(end.back(), A[i]));
	reverse(end.begin(), end.end());

	ll ans = max(end[1], front[N-2]);
	for(int i=1; i<N-1; i++){
		ans = max(ans, gcd(front[i-1], end[i+1]));
	}
	cout << ans << endl;

	return 0;
}
