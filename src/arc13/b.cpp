#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int C,N[100],M[100],L[100];

int main(){
	cin >> C;
	for(int i=0; i<C; i++){
		cin >> N[i] >> M[i] >> L[i];
		if(N[i] > M[i]) swap(N[i], M[i]);
		if(M[i] > L[i]) swap(M[i], L[i]);
		if(N[i] > M[i]) swap(N[i], M[i]);
	}

	vector<int> ans(3, 0);
	for(int i=0; i<C; i++){
		ans[0] = max(ans[0], N[i]);
		ans[1] = max(ans[1], M[i]);
		ans[2] = max(ans[2], L[i]);
	}

	cout << ans[0]*ans[1]*ans[2] << endl;
	return 0;
}
