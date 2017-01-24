#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
using namespace std;
const int Cmax = 1000000;
long C,N,F;
long S[Cmax], A[Cmax];
vector<pair<long, long> > score;

int main(){
	cin >> N >> C >> F;
	for(int i=0; i<C; i++){
		cin >> S[i] >> A[i];
		score.push_back(make_pair(S[i],A[i]));
	}

	sort(score.begin(), score.end());
	
	long lower_min = 0, upper_min = 0;
	priority_queue<pair<long, int>,
		vector<pair<long, int> >, less<pair<long, int> > > upper;
	priority_queue<pair<long, int> > lower;
	set<int> upper_used;

	for(int i=0; i<(N-1)/2; i++){
		lower.push(make_pair(score[i].second, i));
		lower_min += score[i].second;
	}
	for(int i=(N-1)/2+1; i<C; i++){
		upper.push(make_pair(score[i].second, i));
	}
	for(int i=0; i<(N-1)/2; i++){
		upper_min += upper.top().second;
		upper_used.insert(upper.top().first);
		upper.pop();
	}

	long ans = -1;
	for(int i=(N-1)/2; i<C-(N-1)/2; i++){
		if(lower_min + score[i].second + upper_min <= F){
			ans = score[i].first;
		}

		lower.push(make_pair(score[i].second, i));
		lower_min += (score[i].second - lower.top().first);
		lower.pop();

		if(upper_used.find(i+1) != upper_used.end()){
			upper_used.insert(upper.top().second);
			upper_used.erase(i+1);
			upper_min += (upper.top().first - score[i+1].second);
			upper.pop();
		}
		else{
		}

	}

	cout << ans << endl;

	return 0;
}
