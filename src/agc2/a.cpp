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
int a, b;

int main(){
	cin >> a >> b;
	if(a<=0 && b>=0){
		cout << "Zero" << endl;
	} else if(a>0){
		cout << "Positive" << endl;
	} else if((b-a)%2==1){
		cout << "Positive" << endl;
	} else{
		cout << "Negative" << endl;
	}

	return 0;
}
