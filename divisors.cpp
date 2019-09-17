#include<bits/stdc++.h>
typedef long long ll;

// list all divisors of n. O(sqrt(n))
std::vector<ll> get_divisors(ll n){
	std::vector<ll> div(1, 1);
	for(int i=2; i*i<=n; i++){
		if(n%i==0) div.push_back(i);
	}
	for(int i=div.size()-1; i>=0; i--){
		if(div[i]*div[i]==n) continue;
		div.push_back(n/div[i]);
	}
	return div;
}

int main(){
	using namespace std;
	auto div = get_divisors(64);
	for(ll d: div) cout << d << endl;
	return 0;
}
