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

ll naive(ll x, vector<ll> &v, vector<ll> &w){
	int n = v.size();
	map<ll, ll> wv[2];
	for(int p=0; p<2; p++){
		for(int s=0; s<(1<<((n+p)/2)); s++){
			ll vsum = 0;
			ll wsum = 0;
			for(int i=0; i<(n+p)/2; i++){
				if(s>>i&1){
					vsum+=v[p*n/2+i];
					wsum+=w[p*n/2+i];
				}
			}
			if(wsum<=x){
				//dbg(vsum, wsum);
				wv[p][wsum] = max(wv[p][wsum], vsum);
			}
		}

		ll a=0;
		for(auto q: wv[p]){
			a = max(a, q.second);
			wv[p][q.first] = a;
			dbg(q.first, a);
		}
	}

	ll ans = 0;
	for(auto q: wv[0]){
		ll w0 = q.first;
		ll v0 = q.second;
		auto i = wv[1].upper_bound(x-w0);
		i--;
		ll w1 = i->first;
		ll v1 = i->second;
		if(w0+w1<=x){
			ans = max(ans, v0+v1);
		}
	}

	return ans;
}

ll wdp(ll x, vector<ll> &v, vector<ll> &w){
	int n = v.size();
	vector<vector<ll>> dp(n+1, vector<ll>(200005));
	for(int i=0; i<n; i++){
		for(int j=0; j<200005; j++){
			if(j-w[i]>=0){
				dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]]+v[i]);
			} else {
				dp[i+1][j] = dp[i][j];
			}
		}
	}

	ll ans = 0;
	for(int i=0; i<=min(x, 200004ll); i++){
		ans = max(ans, dp[n][i]);
	}
	return ans;
}

ll vdp(ll x, vector<ll> &v, vector<ll> &w){
	int n=v.size();
	vector<vector<ll>> dp(n+1, vector<ll>(200005, 1e18));
	dp[0][0] = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<200005; j++){
			if(j-v[i]>=0){
				dp[i+1][j] = min(dp[i][j], dp[i][j-v[i]]+w[i]);
			} else {
				dp[i+1][j] = dp[i][j];
			}
		}
	}

	int ans = 0;
	for(int i=0; i<200005; i++){
		if(dp[n][i]<=x){
			ans = max(ans, i);
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	ll x;
	cin >> n >> x;
	vector<ll> v(n), w(n);
	for(int i=0; i<n; i++) cin >> v[i] >> w[i];

	ll wsum = 0;
	for(int i=0; i<n; i++) wsum+=w[i];

	ll ans = 0;
	if(n<=30){
		ans = naive(x, v, w);
	} else if(wsum<=200000){
		ans = wdp(x, v, w);
	} else {
		ans = vdp(x, v, w);
	}
	cout << ans << endl;
	return 0;
}
