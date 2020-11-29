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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

void solve(){
    int ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    // make a center
    if(bx==ax&&by==cy||by==ay&&bx==cx){
        swap(ax, bx);
        swap(ay, by);
    }
    else if(cx==ax&&cy==by||cy==ay&&cx==bx){
        swap(ax, cx);
        swap(ay, cy);
    }
    dbg(ax, ay);

    int x = min({ax, bx, cx});
    int y = min({ay, by, cy});
    int t;
    if(ax==x && ay==y) t = 0;
    else if(ax==x && ay==y+1) t = 3;
    else if(ax==x+1&&ay==y+1) t = 2;
    else t = 1;

    dbg(x, y, t);

    int ans;
    if(x==y){
        if(x==0){
            if(t == 0){
                ans = 0;
            } else {
                ans = 1;
            }
        } else if(x>0){
            if(t==2){
                ans = 2*x+2;
            } else {
                ans = 2*x+1;
            }
        } else {
            if(t==0){
                ans = 2*abs(x)+1;
            } else {
                ans = 2*abs(x);
            }
        }
    } else if(x+y>=0){
        if(x>y){
            if(t==0||t==3){
                ans = 2*x;
            } else {
                ans = 2*x+1;
            }
        } else {
            if(t==0||t==1){
                ans = 2*y;
            } else {
                ans = 2*y+1;
            }
        }
    } else {
        if(x<y){
            if(t==0||t==3){
                ans = 2*abs(x);
            } else {
                ans = 2*abs(x)-1;
            }
        } else {
            if(t==0||t==1){
                ans = 2*abs(y);
            } else {
                ans = 2*abs(y)-1;
            }
        }
    }


    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++) solve();
    return 0;
}