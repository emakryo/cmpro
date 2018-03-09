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
int N, K;
string S;

int main(){
	cin >> N >> K;
	cin >> S;

	string U = S, X;
	sort(U.begin(), U.end());

	vector<bool> used(N);
	int match_former = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(used[j]) continue;

			int match_latter = 0;
			vector<bool> used2(N);
			used2[j] = true;
			if(S[i] == U[j]) match_latter += 1;
			for(int k=i+1; k<N; k++){
				for(int l=0; l<N; l++){
					if(used[l] || used2[l] || S[k] != U[l]) continue;
					used2[l] = true;
					match_latter += 1;
					break;
				}
			}
			if(match_former+match_latter >= N-K) {
				used[j] = true;
				X += U[j];
				break;
			}
		}
		if(X[i] == S[i]) match_former += 1;
	}

	cout << X << endl;

	return 0;
}
