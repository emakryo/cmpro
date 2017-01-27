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
	map<char, int> conv;
	conv['b'] = '1';
	conv['c'] = '1';
	conv['d'] = '2';
	conv['w'] = '2';
	conv['t'] = '3';
	conv['j'] = '3';
	conv['f'] = '4';
	conv['q'] = '4';
	conv['l'] = '5';
	conv['v'] = '5';
	conv['s'] = '6';
	conv['x'] = '6';
	conv['p'] = '7';
	conv['m'] = '7';
	conv['h'] = '8';
	conv['k'] = '8';
	conv['n'] = '9';
	conv['g'] = '9';
	conv['z'] = '0';
	conv['r'] = '0';

	int N;
	cin >> N;
	vector<string> ans;
	for(int i=0; i<N; i++){
		string S;
		cin >> S;
		ans.push_back("");
		for(int j=0; j<S.size(); j++){
			char c = ('A' <= S[j] && S[j] <= 'Z') ? (char)(S[j]-'A'+'a') : S[j];
			if(string("aiueoy,.").find(c)!=string::npos) continue;
			*ans.rbegin() += conv[c];
		}
		if(*ans.rbegin() == ""){
			ans.pop_back();
		}
	}

	if(!ans.empty()) cout << ans[0];
	for(int i=1; i<ans.size(); i++){
		cout << " " << ans[i];
	}

	cout << endl;

	return 0;
}
