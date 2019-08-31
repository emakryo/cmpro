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
	string a;
	cin >> a;
	vector<int> x(3000), y(3000);
	for(int i=0; i<a.size(); i++){
		for(int j=0; j<a.size(); j++){
			x[i+j] += (a[a.size()-1-i]-'0')*(a[a.size()-1-j]-'0');
			x[i+j+1] += x[i+j]/10;
			x[i+j] = x[i+j]%10;
		}
	}
	int s = 1;
	for(int i=a.size()-1; i>=0; i++){
		if(a[i]=='9') a[i]='0';
		else{
			a[i]++;
			s = 0;
			break;
		}
	}
	if(s) a = "1"+a;

	for(int i=0; i<a.size(); i++){
		for(int j=0; j<a.size(); j++){
			y[i+j] += (a[a.size()-1-i]-'0')*(a[a.size()-1-j]-'0');
			y[i+j+1] += y[i+j]/10;
			y[i+j] = y[i+j]%10;
		}
	}
	for(int i=30; i>=0; i--){
		cout << x[i] << " " << y[i] << endl;
	}

	return 0;
}
