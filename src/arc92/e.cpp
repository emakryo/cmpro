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
const int Nmax = 1000;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	ll s0=0,s1=0;
	for(int i=0; i<N; i++){
		if(A[i]<0) continue;
		if(i%2==0) s0 += A[i];
		else s1 += A[i];
	}


	ll sum=0;
	vector<int> ans;
	if(s0==0&&s1==0){
		ll imax=0;
		for(int i=0; i<N; i++){
			if(A[imax]<A[i]) imax=i;
		}
		sum = A[imax];
		for(int i=imax+1; i<N; i++){
			ans.push_back(N-i+imax+1);
		}
		for(int i=0; i<imax; i++){
			ans.push_back(1);
		}
	} else {
		int p = s0>s1?0:1;
		sum =  max(s0, s1);
		map<int, bool> use;
		int s=0;
		for(int i=0; i<N; i++){
			if(i%2==p && A[i]>0) use[i]=true;
			else use[i]=false;
		}
		for(int i=N-1; !use[i]; i--){
			ans.push_back(i+1);
			use.erase(i);
		}
		for(int i=0; !use[i]; i++){
			ans.push_back(1);
			use.erase(i);
			s=i+1;
		}
		for(int i=s+2; use.find(i)!=use.end(); i+=2){
			if(use[s]&&use[i]){
				ans.push_back(2);
			} else {
				ans.push_back(3);
			}
		}
	}

	cout << sum << endl;
	cout << ans.size() << endl;
	for(int a: ans){
		cout << a << endl;
	}

	return 0;
}
