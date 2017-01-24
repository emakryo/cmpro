#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int Mmax = 1000000;
ll N,M,P[Mmax];
double A[Mmax], B[Mmax];

int main(){
    cin >> N >> M;
    for(int i=0; i<M; i++) cin >> P[i] >> A[i] >> B[i];

    vector<pair<ll, int> > p(M);
    for(int i=0; i<M; i++){
        p[i] = make_pair(P[i],i);
    }
    sort(p.begin(), p.end());
    int n = 0;
    for(int i=0; i<M; i++){
        P[p[i].second] = n;
        if(i<M-1 && p[i].first != p[i+1].first) n++;
    }

    //for(int i=0; i<M; i++) cout << P[i] << " ";
    //cout << endl;

    int s = 1;
    while(s < M) s*=2;
    vector<double> an(2*s, 1);
    vector<double> bn(2*s, 0);
    double ans_min = 1, ans_max = 1;
    for(int i=0; i<M; i++){
        int k = s+P[i];
        an[k] = A[i];
        bn[k] = B[i];
        //cout << k << " " << an[k] << " " << bn[k]<< endl;
        k /= 2;
        while(k > 0){
            an[k] = an[2*k+1]*an[2*k];
            bn[k] = an[2*k+1]*bn[2*k]+bn[2*k+1];
            //cout << k << " " << an[k] << " " << bn[k]<< endl;
            k /= 2;
        }
        ans_min = min(ans_min, an[1]+bn[1]);
        ans_max = max(ans_max, an[1]+bn[1]);
    }

    cout << setprecision(10) << ans_min << endl;
    cout << setprecision(10) << ans_max << endl;

    return 0;
}
