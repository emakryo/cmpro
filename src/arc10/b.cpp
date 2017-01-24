#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 400;
int N, M[Nmax], D[Nmax];

int main(){
	cin >> N;
	char c;
	for(int i=0; i<N; i++) cin >> M[i] >> c >> D[i];
	vector<pair<int, int> > vec;
	for(int i=0; i<N; i++) vec.push_back(make_pair(M[i],D[i]));
	sort(vec.begin(), vec.end());

	int days[] = {31,29,31,30,31,30,31,31,30,31,30,31};

	vector<bool> holiday(366);
	for(int i=0; i<holiday.size(); i++){
		if(i%7 == 0 || i%7 == 6) holiday[i] = true;
	}

	int start[12];
	start[0] = 0;
	for(int i=1; i<12; i++){
		start[i] = start[i-1]+days[i-1];
	}

	for(int i=0; i<N; i++){
		int d = start[vec[i].first-1]+vec[i].second-1;
		while(holiday[d]){
			d++;
			if(d == holiday.size()){
				d = 0;
				break;
			}
		}
		holiday[d] = true;
	}

	int ans = 0;
	int count = 0;
	for(int i=0; i<holiday.size(); i++){
		if(holiday[i]) count++;
		else count = 0;
		ans = max(ans, count);
	}

	cout << ans << endl;
	return 0;
}
