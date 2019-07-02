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
const int Nmax = 500;
int N, M;
int A[Nmax][Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++) cin >> A[i][j];
	}

	if(M==1){
		int x = 0;
		for(int i=0; i<N; i++) x = x^A[i][0];
		if(x>0){
			cout << "TAK" << endl;
			for(int i=0; i<N; i++) cout << 1 << (i==N-1?'\n':' ');
		} else {
			cout << "NIE" << endl;
		}
		return 0;
	}

	for(int k=0; k<10; k++){
		int d[3] = {0, 0, 0};
		int c = -1;
		for(int i=0; i<N; i++){
			int a=0;
			for(int j=0; j<M; j++) a+=1&(A[i][j]>>k);
			//cout << i << " " << k << " " << a << endl;
			if(a==0) d[0]++;
			else if(a==M) d[2]++;
			else {
				d[1]++;
				c = i;
			}
		}
		//cout << c << endl;
		vector<int> ans(N);
		int a = 0;
		for(int i=0; i<N; i++){
			ans[i] = 1;
			if(i==c) continue;
			a += 1&(A[i][0]>>k);
		}
		if(c < 0){
			if(a%2==0) continue;
		} else {
			for(int j=0; j<M; j++){
				if(a%2){
					if((1&(A[c][j]>>k)) == 0) ans[c]=j+1;
				} else {
					if((1&(A[c][j]>>k)) == 1) ans[c]=j+1;
				}
			}
		}
		cout << "TAK" << endl;
		for(int i=0; i<N; i++) cout << ans[i] << (i==N-1?'\n':' ');
		return 0;
	}

	cout << "NIE" << endl;

	return 0;
}
