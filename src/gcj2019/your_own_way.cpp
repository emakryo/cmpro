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

string solve(int N, string P){
	int px=0, py=0;
	int qx=0, qy=0;
	string x;
	if(P[0]=='E'){
		x += "S";
		px++;
		qy++;
	}
	else{
		x += "E";
		py++;
		qx++;
	}
	for(int i=1; i<2*N-2; i++){
		char s;
		if(px==qx && py==qy){
			s = P[i]=='E'?'S':'E';
		} else if(P[P.size()-1]=='E'){
			if(qx==N-1){
				s = 'S';
			} else {
				s = 'E';
			}
		} else {
			if(qy==N-1){
				s = 'E';
			} else {
				s = 'S';
			}
		}
		if(P[i]=='S'){
			py++;
		} else {
			px++;
		}
		if(s=='S'){
			qy++;
		} else {
			qx++;
		}
		//cout << px << ' ' << py << ' ' << qx << ' ' << qy << ' ' << endl;
		x.push_back(s);
	}
	return x;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		int N;
		string P;
		cin >> N >> P;
		cout << "Case #" << (i+1) << ": " << solve(N, P) << endl;
	}

	return 0;
}
