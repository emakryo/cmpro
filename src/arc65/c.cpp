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
string S;

int main(){
	cin >> S;
	vector<bool> ok(S.size()+1);
	ok[0] = true;

	for(int i=0; i<=S.size(); i++){
		if(i >= 5 && ok[i-5] && S.substr(i-5, 5) == "dream"){
			ok[i] = true;
		}
		else if(i >= 7 && ok[i-7] && S.substr(i-7, 7) == "dreamer"){
			ok[i] = true;
		}
		else if(i >= 5 && ok[i-5] && S.substr(i-5, 5) == "erase"){
			ok[i] = true;
		}
		else if(i >= 6 && ok[i-6] && S.substr(i-6, 6) == "eraser"){
			ok[i] = true;
		}
	}

	// cout << S << endl;
	// for(int i=0; i<ok.size(); i++) cout << ok[i];
	// cout << endl;

	cout << (ok[S.size()] ? "YES" : "NO") << endl;
	return 0;
}
