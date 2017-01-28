#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const string days[] = {
	"Saturday",
	"Friday",
	"Thursday",
	"Wednesday",
	"Tuesday",
	"Monday"};


int main(){
	string s;
	cin >> s;
	for(int i=0; i<6; i++){
		if(s == days[i]){
			cout << i << endl;
			return 0;
		}
	}

	cout << 0 << endl;

	return 0;
}
