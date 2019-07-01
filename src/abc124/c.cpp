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

	int ans0=0, ans1=0;
	for(int i=0; i<S.size(); i++){
		if(i%2){
			ans0 += S[i]=='0'?1:0;
			ans1 += S[i]=='1'?1:0;
		} else {
			ans0 += S[i]=='1'?1:0;
			ans1 += S[i]=='0'?1:0;
		}
	}

	cout << min(ans0, ans1) << endl;

	return 0;
}
