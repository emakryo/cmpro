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

pair<string, string> solve(string S){
	string x1, x2;
	for(int i=0; i<S.length(); i++){
		if(S[i] == '4'){
			x1.push_back('3');
			x2.push_back('1');
		}
		else{
			x1.push_back(S[i]);
			x2.push_back('0');
		}
	}

	int i=0;
	while(x2[i]=='0' && i<x2.size()-1) i++;
	if(i>0) x2 = x2.substr(i, x2.size()-i);
	return make_pair(x1, x2);
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		string S;
		cin >> S;
		pair<string, string> ans = solve(S);
		cout << "Case #" << (i+1) << ": " << ans.first << " " << ans.second << endl;
	}

	return 0;
}
