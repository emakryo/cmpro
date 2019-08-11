#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 1e5;
ll X[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		string s;
		cin >> s;
		sort(s.begin(), s.end());
		for(int k=0; k<10; k++){
			X[i] += ((ll)(s[k]-'a'))<<(6*k);
		}
	}

	map<ll, ll> cnt;
	for(int i=0; i<N; i++) cnt[X[i]]++;

	ll ans = 0;
	for(auto p: cnt){
		//cout << p.first << " " << p.second << endl;
		ans += p.second*(p.second-1)/2;
	}

	cout << ans << endl;

	return 0;
}
