#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int Nmax = 30000;
int N;
vector<pair<int, int> > vec;

int main(){
    cin >> N;
    string s;
    getline(cin, s);
    for(int i=0; i<N; i++){
        getline(cin, s);
        int so,sm,eo,em;
        so = atoi(s.substr(0,2).c_str());
        sm = atoi(s.substr(2,2).c_str());
        eo = atoi(s.substr(5,2).c_str());
        em = atoi(s.substr(7,2).c_str());
        sm = (sm/5)*5;
        em = (em/5 + (em%5 == 0 ? 0 : 1))*5;
        vec.push_back(make_pair(so*60+sm, eo*60+em));
        //cout << sm << " " << em << endl;
    }

    vec.push_back(make_pair(25*60,25*60+1));

    sort(vec.begin(), vec.end());

    int start=vec[0].first;
    int end=vec[0].second;
    for(int i=1; i<N+1; i++){
        if(end < vec[i].first){
            cout << setfill('0') << setw(2) << start/60;
            cout << setfill('0') << setw(2) << start%60;
            cout << '-';
            cout << setfill('0') << setw(2) << end/60;
            cout << setfill('0') << setw(2) << end%60 << endl;
            start = vec[i].first;
            end = vec[i].second;
        }
        else{
            end = max(end, vec[i].second);
        }
    }

    return 0;
}
