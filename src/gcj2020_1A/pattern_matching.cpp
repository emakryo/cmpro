#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	int N;
	cin >> N;
	vector<string> P(N);
	for(int i=0; i<N; i++) cin >> P[i];

	vector<string> pre, post, inter;
	for(int i=0; i<N; i++){
		int a=0;
		int b=0;
		while(b<P[i].size() && P[i][b]!='*') b++;
		pre.push_back(P[i].substr(a, b-a));
		a = b+1;
		while(a<P[i].size() && P[i][a]=='*') a++;
		while(a<P[i].size()){
			b=a;
			while(b<P[i].size() && P[i][b]!='*') b++;
			if(b==P[i].size()){
				break;
			} else {
				inter.push_back(P[i].substr(a, b-a));
				a = b+1;
			}
			while(a<P[i].size() && P[i][a]=='*') a++;
		}
		post.push_back(P[i].substr(a, b-a));
	}

	string ans;
	int len_max = pre[0].size();
	int len_max_id = 0;
	for(int i=1; i<N; i++){
		if(pre[i].size() <= len_max){
			if(pre[i] != pre[len_max_id].substr(0, pre[i].size())){
				cout << "*" << endl;
				return;
			}
		} else {
			if(pre[i].substr(0, pre[len_max_id].size()) != pre[len_max_id]){
				cout << "*" << endl;
				return;
			}
			len_max = pre[i].size();
			len_max_id = i;
		}
	}
	ans += pre[len_max_id];

	for(auto &s: inter){
		ans += s;
	}

	len_max = post[0].size();
	len_max_id = 0;
	for(int i=1; i<N; i++){
		int len = post[i].size();
		if(len <= len_max){
			if(post[i] != post[len_max_id].substr(len_max-len)){
				cout << "*" << endl;
				return;
			}
		} else {
			if(post[i].substr(len-len_max) != post[len_max_id]){
				cout << "*" << endl;
				return;
			}
			len_max = len;
			len_max_id = i;
		}
	}
	ans += post[len_max_id];

	cout << ans << endl;
}

int main(){
	int T;
	cin >> T;
	for(int t=1; t<=T; t++){
		cout << "Case #" << t << ": ";
		solve();
	}

	return 0;
}
