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
const int P = 1000000007;
int N, K;
string S;

int main(){
	cin >> N >> K;
	cin >> S;

	vector<vector<int> > count(N-K+1, vector<int>(26));
	for(int i=0; i<K; i++){
		count[0][S[i]-'a']++;
	}
	for(int i=1; i<=N-K; i++){
		for(int j=0; j<26; j++){
			count[i][j] = count[i-1][j];
		}
		count[i][S[i+K-1]-'a']++;
		count[i][S[i-1]-'a']--;

		for(int j=0; j<26; j++){
			//cout << count[i][j] << (j==25?'\n':' ');
		}
	}

	vector<pair<ll, int> > hash;
	for(int i=0; i<=N-K; i++){
		ll key = 0;
		for(int j=0; j<26; j++){
			key *= K;
			key %= P;
			key += count[i][j];
			key %= P;
		}
		hash.push_back(make_pair(key, i));
	}
	sort(hash.begin(), hash.end());

	for(int i=0; i<=N-K; i++){
		int j=i+1;
		for(int j=i+1; hash[j].first==hash[i].first; j++){
			if(abs(hash[i].second - hash[j].second) < K) continue;
			bool match = true;
			for(int k=0; k<26; k++){
				if(count[hash[i].second][k] != count[hash[j].second][k]){
					match = false;
				}
			}
			if(match){
				cout << "YES" << endl;
				return 0;
			}
		}
	}

	cout << "NO" << endl;

	return 0;
}
