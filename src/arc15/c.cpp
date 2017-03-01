#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 200;
int N;
string L[Nmax], S[Nmax];
ll M[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> L[i] >> M[i] >> S[i];
	}

	vector<string> units;
	for(int i=0; i<N; i++){
		if(find(units.begin(), units.end(), S[i]) == units.end()){
			units.push_back(S[i]);
		}
		if(find(units.begin(), units.end(), L[i]) == units.end()){
			units.push_back(L[i]);
		}
	}

	int nu = units.size();
	/*
	for(int i=0; i<nu; i++) cout << units[i] << " ";
	cout << endl;
	*/

	vector<int> li(N);
	vector<int> si(N);
	vector<vector<pair<int, double> > > graph(nu);
	for(int i=0; i<N; i++){
		li[i] = find(units.begin(), units.end(), L[i]) - units.begin();
		si[i] = find(units.begin(), units.end(), S[i]) - units.begin();
		graph[si[i]].push_back(make_pair(li[i], M[i]));
		graph[li[i]].push_back(make_pair(si[i], 1.0/M[i]));
	}

	/*
	for(int i=0; i<nu; i++){
		for(int j=0; j<graph[i].size(); j++){
			cout << "(" << graph[i][j].first << " " << graph[i][j].second << ")" << endl;
		}
		cout << endl;
	}
	*/
	ll ans = 0;
	int ans_s, ans_l;

	for(int i=0; i<nu; i++){
		vector<double> scale(nu);
		scale[i] = 1;

		queue<int> que;
		que.push(i);
		while(!que.empty()){
			int s = que.front();
			que.pop();
			
			for(int j=0; j<graph[s].size(); j++){
				int l = graph[s][j].first;
				double m = graph[s][j].second;
				if(scale[l] != 0) continue;
				//cout << units[l] << m << endl;
				scale[l] = scale[s]*m;
				que.push(l);
			}
		}

		for(int j=0; j<nu; j++){
			if(scale[j] == 0) continue;
			if(ans < scale[j]){
				ans = (ll)round(scale[j]);
				ans_s = i;
				ans_l = j;
			}
		}
	}

	cout << 1 << units[ans_l] << "=" << ans << units[ans_s] << endl;

	return 0;
}
