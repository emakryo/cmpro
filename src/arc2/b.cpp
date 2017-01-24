#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int Y,M,D;
const int Dmax[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool uruu(int y){
	if(y%400==0) return true;
	else if(y%100==0) return false;
	else if(y%4==0) return true;
	else return false;
}

int main(){
	char s;
	cin >> Y >> s >> M >> s >> D;

	while(Y % (M * D) != 0){
		if(uruu(Y) && M == 2 && D == 28){
			D++;
		}
		else if(M == 12 && D == 31){
			Y++;
			M = 1;
			D = 1;
		}
		else if(D >= Dmax[M-1]){
			M++;
			D = 1;
		}
		else{
			D++;
		}
	}

	cout << Y << '/';
	cout << setw(2) << setfill('0') << M << '/';
	cout << setw(2) << setfill('0') << D << endl;

	return 0;
}

