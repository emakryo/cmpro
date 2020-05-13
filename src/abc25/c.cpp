#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int b[2][3], c[3][2];
	int sum = 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<3; j++){
			cin >> b[i][j];
			sum+=b[i][j];
		}
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
			cin >> c[i][j];
			sum+=c[i][j];
		}
	}

	vector<int> dp(1<<18);
	for(int s=(1<<18); s; s--){
		int t = s-1;
		int na=0, nb=0;
		int xa=0, xb=0;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				int k = (t>>(2*(3*i+j)))&3;
				if(k==0||k==3) continue;
				if(k==1) na++;
				if(k==2) nb++;
				if(i<2){
					int l = (t>>(2*(3*(i+1)+j)))&3;
					if(k==l){
						xa+=b[i][j];
					}  else {
						xb+=b[i][j];
					}
				}
				if(j<2){
					int l = (t>>(2*(3*i+j+1)))&3;
					if(k==l){
						xa+=c[i][j];
					} else {
						xb+=c[i][j];
					}
				}
			}
		}
		if(na==5&&nb==4){
			dp[t] = xa-xb;
			dbg(t, dp[t]);
			continue;
		} else if(na-nb==0){
			dp[t] = -1e9;
		} else if(na-nb==1){
			dp[t] = 1e9;
		} else {
			continue;
		}
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				int k = t>>(2*(3*i+j))&3;
				if(k>0) continue;
				if(na-nb==0){
					dp[t] = max(dp[t|(1<<(2*(3*i+j)))], dp[t]);
				}
				if(na-nb==1){
					dp[t] = min(dp[t|(2<<(2*(3*i+j)))], dp[t]);
				}
			}
		}
	}

	cout << (dp[0]+sum)/2 << endl;
	cout << (sum-dp[0])/2 << endl;

	return 0;
}
