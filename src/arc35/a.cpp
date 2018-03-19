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

int main(){
	string S;
	cin >> S;

	for(int i=0; i<S.size()/2; i++){
		int j = S.size()-i-1;
		if(S[i] != '*' && S[j] != '*' && S[i] != S[j]){
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;

	return 0;
}
