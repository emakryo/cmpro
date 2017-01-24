#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const ll P = 1000000007;
const int Nmax = 100000;
int N;
int A[Nmax];
int cnt[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> A[i];
		cnt[A[i]]++;
	}

	/*
	for(int i=0; i<N; i++) cout << cnt[i] << " ";
	cout << endl;
	*/

	bool ok = true;
	if(N%2==0){
		ok = (cnt[0] == 0);
		for(int i=1; i<N; i++){
			if(i%2 == 0){
				ok = (ok && cnt[i]== 0);
			}
			else{
				ok = (ok && cnt[i] == 2);
			}
		}

	}
	else{
		ok = (cnt[0] == 1);
		for(int i=1; i<N; i++){
			if(i%2 == 0){
				ok = (ok && cnt[i] == 2);
			}
			else{
				ok = (ok && cnt[i] == 0);
			}
		}
	}

	ll ans = 1;
	if(ok){
		for(int i=0; i<N/2; i++){
			ans = 2*ans%P;
		}
		cout << ans << endl;
	}
	else{
		cout << 0 << endl;
	}
	return 0;
}
