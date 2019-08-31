#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, L;
string S;

int main(){
	cin >> N >> L;
	cin >> S;

	int ans = 0;
	int ntab = 1;
	for(int i=0; i<N; i++){
		if(S[i]=='+') ntab++;
		else ntab--;
		if(ntab > L){
			ans++;
			ntab=1;
		}
	}

	cout << ans << endl;

	return 0;
}
