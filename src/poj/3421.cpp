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
	vector<int> prime;
	int k=1;
	int p=3;
	prime.push_back(2);
	while(p < 1024){
		bool is_p = true;
		for(int i=0; i<k; i++){
			if(p%prime[i]==0){
				is_p = false;
				break;
			}
		}
		if(is_p){
			prime.push_back(p);
			k++;
		}
		p += 2;
	}

	int np=prime.size();
	//for(int i=0; i<10; i++) cout << prime[i] << " " << prime[np-i] << endl;

	ll X;
	while(cin >> X){
		vector<int> decomp(np);
		int k=0;
		while(k < np){
			if(X%prime[k] == 0){
				decomp[k]++;
				X /= prime[k];
			}
			else k++;
		}
		int length = 0;
		for(int i=0; i<np; i++) length+=decomp[i];
		if(X > 1) length++;

		int remain = length;
		ll number = 1;
		for(int i=0; i<np; i++){
			for(int j=0; j<decomp[i]; j++){
				number *= remain;
				remain--;
			}
			for(int j=0; j<decomp[i]; j++){
				number /= j+1;
			}
		}

		cout << length << " " << number << endl;
	}


	return 0;
}
