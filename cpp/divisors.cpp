#include<bits/stdc++.h>

// list all divisors of n. O(sqrt(n))
std::vector<long long> get_divisors(long long n){
	std::vector<long long> div(1, 1);
	for(int i=2; (long long)i*i<=n; i++){
		if(n%i==0) div.push_back(i);
	}
	for(int i=div.size()-1; i>=0; i--){
		if(div[i]*div[i]==n) continue;
		div.push_back(n/div[i]);
	}
	return div;
}
