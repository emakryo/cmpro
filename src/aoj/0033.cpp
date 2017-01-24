#include<iostream>
#include<algorithm>
using namespace std;
int N;
int X[10];

bool dfs(int i, int a, int b){
	if(i==10) return true;
	//cout << i << " " << a << " " << b << endl;
	if(X[i] > a && dfs(i+1, X[i], b)) return true;
	if(X[i] > b && dfs(i+1, a, X[i])) return true;
	return false;
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		for(int j=0; j<10; j++) cin >> X[j];

		cout << (dfs(0,0,0) ? "YES" : "NO") << endl;
	}
	return 0;
}
