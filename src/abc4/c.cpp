#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
ll N;

void pprod(int p[6], int q[6], int r[6]){
	for(int i=0; i<6; i++){
		r[i] = p[q[i]];
	}
}

void ppow(int p[6], ll m, int q[6]){
	if(m==0){
		for(int i=0; i<6; i++) q[i]=i;
	}
	else if(m==1){
		for(int i=0; i<6; i++) q[i]=p[i];
	}
	else if(m%2==1){
		int r[6];
		ppow(p, m-1, r);
		pprod(p, r, q);
	}
	else{
		int r[6];
		ppow(p, m/2, r);
		pprod(r, r, q);
	}
}

int main(){
	cin >> N;

	int a[] = {0,1,2,3,4,5};
	for(int i=0; i<5; i++){
		swap(a[i],a[i+1]);
	}
	int b[6];
	
	ppow(a, N/5, b);
	for(int i=0; i<N%5; i++){
		swap(b[i], b[i+1]);
	}

	for(int i=0; i<6; i++){
		cout << b[i]+1;
	}
	cout << endl;

	return 0;
}
