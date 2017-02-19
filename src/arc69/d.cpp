#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int N;
string S;
bool ans[100001];

int main(){
	cin >> N >> S;
	bool init[4][2] = {{1,1},{1,0},{0,1},{0,0}};
	for(int i=0; i<4; i++){
		ans[0] = init[i][0];
		ans[1] = init[i][1];
		for(int j=2; j<N; j++){
			if(ans[j-1]){
				if(S[j-1]=='o'){
					ans[j] = ans[j-2];
				}
				else{
					ans[j] = !ans[j-2];
				}
			}
			else{
				if(S[j-1]=='o'){
					ans[j] = !ans[j-2];
				}
				else{
					ans[j] = ans[j-2];
				}
			}
		}
		if(((ans[N-1]==ans[1]) == (ans[0]^(S[0]!='o'))) &&
				((ans[N-2] == ans[0]) == (ans[N-1]^(S[N-1]!='o')))){
			for(int j=0; j<N; j++){
				cout << (ans[j] ? 'S' : 'W');
			}
			cout << endl;
			return 0;
		}
	}
	cout << -1 << endl;

	return 0;
}
