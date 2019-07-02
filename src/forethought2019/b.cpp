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
	string t;
	cin >> t;

	string ss;
	for(int i=0; i<t.size(); i++){
		if(t[i]!='a') ss += t[i];
	}
	
	if(ss.size()%2){
		cout << ":(" << endl;
		return 0;
	}

	for(int i=0; i<ss.size()/2; i++){
		if(ss[i]!=ss[i+ss.size()/2]){
			cout << ":(" << endl;
			return 0;
		}
	}

	for(int i=0; i<ss.size()/2; i++){
		if(t[t.size()-1-i]=='a'){
			cout << ":(" << endl;
			return 0;
		}
	}

	cout << t.substr(0, t.size()-ss.size()/2) << endl;

	return 0;
}
