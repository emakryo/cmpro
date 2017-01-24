#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int CLmax = 2501;
int C,L;
int Smin[CLmax], Smax[CLmax];
int S[CLmax], V[CLmax];

int main(){
	cin >> C >> L;
	for(int i=0; i<C; i++){
		cin >> Smin[i] >> Smax[i];
	}
	for(int i=0; i<L; i++){
		cin >> S[i] >> V[i];
	}

	vector<pair<int, int> > order1, order2;

	for(int i=0; i<C; i++){
		order1.push_back(make_pair(Smax[i], Smin[i]));
	}

	for(int i=0; i<L; i++){
		order2.push_back(make_pair(S[i], V[i]));
	}

	sort(order1.begin(), order1.end());
	sort(order2.begin(), order2.end());

	int ans = 0;
	for(int i=0; i<C; i++){
		for(int j=0; j<L; j++){
			if(order1[i].second <= order2[j].first && order2[j].first <= order1[i].first
				&& order2[j].second){
				ans ++;
				order2[j].second--;
				break;
			}
		}
	}
	
	cout << ans << endl;

	return 0;
}
