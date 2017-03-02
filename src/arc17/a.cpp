#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N;
	cin >> N;

	vector<int> prime;
	prime.push_back(2);
	for(int i=3; i*i<=N; i+=2){
		bool is_prime = true;
		for(int j=0; j<prime.size(); j++){
			if(i%prime[j]==0){
				is_prime = false;
				break;
			}
		}
		if(is_prime) prime.push_back(i);
	}

	bool ans=true;
	for(int i=0; i<prime.size() && prime[i]*prime[i]<=N; i++){
		if(N%prime[i] == 0){
			ans = false;
			break;
		}
	}

	cout << (ans ? "YES" : "NO") << endl;

	return 0;
}
