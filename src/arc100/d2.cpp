#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];

    vector<ll> c(n);
    c[0] = a[0];
    for(int i=1; i<n; i++) c[i] = a[i]+c[i-1];

    ll ans = 1e18;
    for(int i=2; i<n-1; i++){
        int ci = lower_bound(c.begin(), c.end(), c[i-1]/2)-c.begin();
        int ei = lower_bound(c.begin(), c.end(), c[i-1]+(c[n-1]-c[i-1])/2)-c.begin();

        ll p = c[ci];
        ll q = c[i-1]-p;
        ll r = c[ei]-c[i-1];
        ll s = c[n-1]-c[ei];

        ans = min(ans, max({p, q, r, s}) - min({p, q, r, s}));
        ans = min(ans, max({p-a[ci], q+a[ci], r, s}) - min({p-a[ci], q+a[ci], r, s}));
        ans = min(ans, max({p, q, r-a[ei], s+a[ei]}) - min({p, q, r-a[ei], s+a[ei]}));
        ans = min(ans, max({p-a[ci], q+a[ci], r-a[ei], s+a[ei]}) - min({p-a[ci], q+a[ci], r-a[ei], s+a[ei]}));
    }

    cout << ans << endl;
    return 0;
}