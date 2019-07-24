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

	int red=0;
	for(int i=0; i<S.size(); i++) if(S[i]=='0') red++;
	int blue = S.size()-red;

	cout << 2*min(blue, red) << endl;

	return 0;
}
