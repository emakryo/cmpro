//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 5000;
int T, N, L[Nmax], W[Nmax];

int main(){
	scanf("%d", &T);

	for(int iii=0; iii<T; iii++){
		scanf("%d", &N);
		vector<pair<int, int> > vec;
		for(int i=0; i<N; i++){
			int l,w;
			scanf("%d%d", &l, &w);
			vec.push_back(make_pair(l,w));
		}

		sort(vec.begin(), vec.end());

		vector<int> last;
		last.push_back(vec[0].second);
		
		for(int i=1; i<N; i++){
			//printf(" %d\n", vec[i].second);
			if(vec[i].second < last[last.size()-1]){
				last.push_back(vec[i].second);
			}
			else{
				vector<int>::reverse_iterator j =
					--upper_bound(last.rbegin(), last.rend(), vec[i].second);
				*j = vec[i].second;
			}
			//for(int j=0; j<last.size(); j++) printf("%d ", last[j]);
			//puts("");
		}

		printf("%d\n", (int)last.size());
	}

	return 0;
}
