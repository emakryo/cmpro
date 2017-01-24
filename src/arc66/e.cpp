#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
int N;
ll A[Nmax];
string Op;

int main(){
	cin >> N;
	cin >> A[0];
	for(int i=0; i<N-1; i++){
		string s;
		cin >> s >> A[i+1];
		Op += s;
	}

	for(int i=0; i<N; i++) cout << A[i] << " ";
	cout << endl;
	for(int i=0; i<Op.size(); i++) cout << Op[i] << " ";
	cout << endl;


	return 0;
}
