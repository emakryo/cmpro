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
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	vector<pair<int, int>> ab(n);
	for(int i=0; i<n; i++) cin >> ab[i].first >> ab[i].second;
	sort(ab.begin(), ab.end());

	priority_queue<int> que;
	int j=0;
	int ans = 0;
	for(int i=0; i<n; i++){
		while(ab[j].first<=i+1){
			que.push(ab[j].second);
			j++;
		}
		ans += que.top();
		que.pop();
		cout << ans << endl;
	}

	return 0;
}
