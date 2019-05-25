#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
int Q;

int main(){
    cin >> Q;
    priority_queue<ll, vector<ll>, greater<ll> > large;
    priority_queue<ll> small;
    ll constant = 0, lsum=0, ssum=0;
    for(int i=0; i<Q; i++){
        int t;
        ll a, b;
        cin >> t;
        if(t==1){
            cin >> a >> b;
            constant += b;
            if(large.size() >= small.size()){
                small.push(a);
                ssum += a;
            } else {
                large.push(a);
                lsum += a;
            }

            if(large.size()==0) continue;
            ll l = large.top();
            ll s = small.top();
            if(l < s){
                large.pop();
                small.pop();
                large.push(s);
                small.push(l);
                lsum += s-l;
                ssum += l-s;
            }
        } else {
            ll s = small.top();
            // cout << s*small.size() << " " << ssum << " " << s*large.size() << " " << lsum << " " << constant << endl;
            cout << s << " " << (s*(ll)small.size()-ssum) + (lsum-s*(ll)large.size()) + constant << endl;
        }
    }
    return 0;
}