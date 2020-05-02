
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

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
	int N;
	cin >> N;
	vector<int> S(N), T(N);
	vector<ll> U(N), V(N);
	for(int i=0; i<N; i++) cin >> S[i];
	for(int i=0; i<N; i++) cin >> T[i];
	for(int i=0; i<N; i++) cin >> U[i];
	for(int i=0; i<N; i++) cin >> V[i];

	vector<vector<ll>> ans(N, vector<ll>(N));

	for(int k=0; k<64; k++){
		vector<int> cx0(N);
		vector<int> cx1(N);
		vector<int> cy0(N);
		vector<int> cy1(N);
		vector<vector<int>> a(N, vector<int>(N, -1));
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				int u = U[i]>>k&1;
				int v = V[j]>>k&1;
				if(S[i]==0&&u==1&&T[j]==1&&v==0 || S[i]==1&&u==0&&T[j]==0&&v==1){
					cout << -1 << endl;
					return 0;
				} else if(S[i]==0&&u==1||T[j]==0&&v==1){
					a[i][j]=1;
					cx1[i]++;
					cy1[j]++;
				} else if(T[j]==1&&v==0||S[i]==1&&u==0){
					a[i][j]=0;
					cx0[i]++;
					cy0[j]++;
				} else if(u==0&&v==0){
					a[i][j]=0;
					cx0[i]++;
					cy0[j]++;
				} else if(u==1&&v==1){
					a[i][j]=1;
					cx1[i]++;
					cy1[j]++;
				}
			}
		}

		while(true){
			bool change = false;
			for(int i=0; i<N; i++){
				int u=U[i]>>k&1;
				if(S[i]==0&&u==0){
					if(cx0[i]==0&&cx1[i]==N){
						cout << -1 << endl;
						return 0;
					} else if(cx0[i]==0&&cx1[i]==N-1){
						for(int j=0; j<N; j++) if(a[i][j]<0){
							change=true;
							a[i][j]=0;
							cx0[i]++;
							cy0[j]++;
						}
					}
				} else if(S[i]==1&&u==1){
					if(cx1[i]==0&&cx0[i]==N){
						cout << -1 << endl;
						return 0;
					} else if(cx1[i]==0&&cx0[i]==N-1){
						for(int j=0; j<N; j++) if(a[i][j]<0){
							change=true;
							a[i][j]=1;
							cx1[i]++;
							cy1[j]++;
						}
					}
				}
			}

			for(int j=0; j<N; j++){
				int v=V[j]>>k&1;
				if(T[j]==0&&v==0){
					if(cy0[j]==0&&cy1[j]==N){
						cout << -1 << endl;
						return 0;
					} else if(cy0[j]==0&&cy1[j]==N-1){
						for(int i=0; i<N; i++) if(a[i][j]<0){
							change=true;
							a[i][j]=0;
							cx0[i]++;
							cy0[j]++;
						}
					}
				} else if(T[j]==1&&v==1){
					if(cy1[j]==0&&cy0[j]==N){
						cout << -1 << endl;
						return 0;
					} else if(cy1[j]==0&&cy0[j]==N-1){
						for(int i=0; i<N; i++) if(a[i][j]<0){
							change=true;
							a[i][j]=1;
							cx1[i]++;
							cy1[j]++;
						}
					}
				}
			}
			if(!change) break;
		}

		vector<int> is, js;
		for(int i=0; i<N; i++){
			if(cx0[i]+cx1[i]<N) is.push_back(i);
			if(cy0[i]+cy1[i]<N) js.push_back(i);
		}
		for(int i=0; i<is.size(); i++){
			for(int j=0; j<js.size(); j++){
				a[is[i]][js[j]] = (i+j)%2;
			}
		}

		for(int i=0; i<N; i++){
			int u=1-S[i];
			for(int j=0; j<N; j++){
				if(S[i]){
					u |= a[i][j];
				} else {
					u &= a[i][j];
				}
			}
			assert(u==(U[i]>>k&1));
		}
		for(int j=0; j<N; j++){
			int v=1-T[j];
			for(int i=0; i<N; i++){
				if(T[j]){
					v |= a[i][j];
				} else {
					v &= a[i][j];
				}
			}
			assert(v==(V[j]>>k&1));
		}


		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				assert(a[i][j]>=0);
				ans[i][j] |= (ll)a[i][j] << k;
			}
		}
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cout << ans[i][j] << (j<N-1?" ":"\n");
		}
	}

	return 0;
}
