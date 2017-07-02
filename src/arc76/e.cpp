#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<complex>
using namespace std;
typedef long long ll;
typedef complex<double> Point;
const int Nmax = 1e5;
int N;
ll R, C;
ll X1[Nmax], Y1[Nmax], X2[Nmax], Y2[Nmax];

bool onEdge(ll x, ll y){
	return x==0 || x==R || y==0 || y==C;
}

ll linear(ll x, ll y){
	if(y == 0){
		return x;
	}
	else if(x == R){
		return R+y;
	}
	else if(y == C){
		return R+R+C-x;
	}
	else{
		return 2*R+2*C-y;
	}
}


int main(){
	cin >> R >> C >> N;
	for(int i=0; i<N; i++){
		cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
	}

	vector<pair<ll, int> > vec;
	for(int i=0; i<N; i++){
		if(onEdge(X1[i], Y1[i]) && onEdge(X2[i], Y2[i])){
			vec.push_back(make_pair(linear(X1[i], Y1[i]), i));
			vec.push_back(make_pair(linear(X2[i], Y2[i]), i));
		}
	}

	sort(vec.begin(), vec.end());

	stack<int> st;
	vector<bool> instack(N);
	for(int i=0; i<vec.size(); i++){
		//cout << vec[i].first << " " << vec[i].second << endl;
		if(instack[vec[i].second]){
			if(st.top() != vec[i].second){
				cout << "NO" << endl;
				return 0;
			}
			else{
				st.pop();
				instack[vec[i].second] = false;
			}
		}
		else{
			st.push(vec[i].second);
			instack[vec[i].second] = true;
		}
	}

	cout << "YES" << endl;

	return 0;
}
