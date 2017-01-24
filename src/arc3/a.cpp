#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int N;
string R;

int main(){
	cin >> N;
	cin >> R;

	double sum = 0;
	for(int i=0; i<R.size(); i++){
		switch(R[i]){
			case 'A':
				sum += 4;
				break;
			case 'B':
				sum += 3;
				break;
			case 'C':
				sum += 2;
				break;
			case 'D':
				sum += 1;
				break;
		}
	}

	cout << setprecision(10) << sum / N << endl;
	return 0;
}
