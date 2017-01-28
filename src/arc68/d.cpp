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
const int Nmax = 100000;
int N,A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> A[i];
		A[i]--;
	}

	sort(A, A+N);
	vector<int> cnt(100000);
	for(int i=0; i<N; i++){
		cnt[A[i]]++;
	}

	int l=0, u=100000-1;
	while(l < 100000 && cnt[l]<2) l++;
	while(u >= 0 && cnt[u]<2) u--;
	while(l<u){
		cnt[l]--;
		cnt[u]--;
		while(l < 100000 && cnt[l]<2) l++;
		while(u >= 0 && cnt[u]<2) u--;
	}
	
	int ans = 0;
	if(l == u){
		while(cnt[l] >= 3) cnt[l]-= 2;
		if(cnt[l]>1){
			cnt[l] = 1;
			ans = -1;
		}
	}

	for(int i=0; i<100000; i++){
		if(cnt[i]==1) ans++;
	}

	cout << ans << endl;


	return 0;
}
