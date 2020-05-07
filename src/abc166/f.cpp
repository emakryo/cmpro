#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
	ll A, B, C;
	cin >> A >> B >> C;

	vector<string> S(N);
	for(int i=0; i<N; i++) cin >> S[i];

	vector<char> ans;
	for(int i=0; i<N; i++){
		char next;
		if(S[i]=="AB"){
			if(A==0&&B==0) break;
			if(A==0) next = 'A';
			else if(B==0) next = 'B';
			else if(i<N-1 && S[i+1]=="BC") next='B';
			else next='A';
			if(next=='A'){
				A++;
				B--;
			} else {
				A--;
				B++;
			}
		} else if(S[i]=="BC"){
			if(C==0&&B==0) break;
			if(C==0) next = 'C';
			else if(B==0) next = 'B';
			else if(i<N-1 && S[i+1]=="AC") next='C';
			else next='B';
			if(next=='B'){
				B++;
				C--;
			} else {
				B--;
				C++;
			}
		} else {
			if(C==0&&A==0) break;
			if(C==0) next = 'C';
			else if(A==0) next = 'A';
			else if(i<N-1 && S[i+1]=="BC") next='C';
			else next='A';
			if(next=='A'){
				A++;
				C--;
			} else {
				A--;
				C++;
			}
		}
		ans.push_back(next);
	}
	if(ans.size()<N){
		cout << "No" << endl;
	} else {
		cout << "Yes" << endl;
		for(int i=0; i<N; i++){
			cout << ans[i] << endl;
		}
	}

	return 0;
}
