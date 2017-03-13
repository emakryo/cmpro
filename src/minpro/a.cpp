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
	string s;
	cin >> s;
	map<char, int> count;
	for(int i=0; i<s.size(); i++){
		if(s[i]!='y'&&s[i]!='a'&&s[i]!='h'&&s[i]!='o'){
			cout << "NO" << endl;
			return 0;
		}
		count[s[i]]++;
	}
	if(count['y']==1&&count['a']==1&&count['h']==1&&count['o']==2){
		cout << "YES" << endl;
	}
	else{
		cout << "NO" << endl;
	}

	return 0;
}
