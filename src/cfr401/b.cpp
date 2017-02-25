#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1000;
int N;
int A[Nmax], B[Nmax];
int main(){
	cin >> N;
	string sa, sb;
	cin >> sa >> sb;

	for(int i=0; i<N; i++){
		A[i] = sa[i]-'0';
		B[i] = sb[i]-'0';
	}

	sort(A, A+N);
	sort(B, B+N);

	int ans_min = N;
	int k = N-1;
	for(int i=N-1; i>=0; i--){
		if(B[k] >= A[i]){
			k--;
			ans_min--;
		}
	}

	int ans_max = 0;
	k = N-1;
	for(int i=N-1; i>= 0; i--){
		if(B[k] > A[i]){
			k--;
			ans_max++;
		}
	}

	cout << ans_min << endl;
	cout << ans_max << endl;

	return 0;
}
