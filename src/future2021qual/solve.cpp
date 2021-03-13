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

using pii = pair<int, int>;

int eval(string &ans){
    int x = 0;
    for(char c: ans){
        if(c=='D'||c=='U'||c=='R'||c=='L') x++;
    }
    return 4000-x;
}

string naive(vector<pair<int, int>> const &pos, pair<int, int> init){
    string ans;
    for(int i=0; i<pos.size(); i++){
        int dx = pos[i].first - init.first;
        for(int k=0; k<abs(dx); k++){
            if(dx>0) ans.push_back('D');
            else ans.push_back('U');
        }
        int dy = pos[i].second - init.second;
        for(int k=0; k<abs(dy); k++){
            if(dy>0) ans.push_back('R');
            else ans.push_back('L');
        }

        ans.push_back('I');
        init = pos[i];
    }
    return ans;
}

string align(vector<pair<int, int>> &pos, pair<int, int> &init){
    vector<vector<int>> board(20, vector<int>(20, -1));
    for(int i=0; i<pos.size(); i++){
        int x = pos[i].first;
        int y = pos[i].second;
        board[x][y] = i;
    }

    vector<int> stack;
    string out;
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            int k = i%2?19-j:j;
            if(board[i][k]>=0){
                out.push_back('I');
                stack.push_back(board[i][k]);
                board[i][k] = -1;
            }
            if(i%2){
                if(j==19){
                    if(i!=19){
                        out.push_back('D');
                        init.first++;
                    }
                } else {
                    out.push_back('L');
                    init.second--;
                }
            } else {
                if(j==19){
                    out.push_back('D');
                    init.first++;
                } else {
                    out.push_back('R');
                    init.second++;
                }
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            int x = 19-i;
            int y = i%2?9-j:j;
            int k = stack.back();
            out.push_back('O');
            board[x][y] = k;
            stack.pop_back();
            pos[k] = {x, y};

            if(j==9){
                if(i!=9){
                    out.push_back('U');
                    init.first--;
                }
            } else {
                if(x%2){
                    out.push_back('R');
                    init.second++;
                } else {
                    out.push_back('L');
                    init.second--;
                }
            }
        }
    }

    for(int i=0; i<20; i++){
        dbg(board[i]);
    }
    dbg(init.first, init.second);
    dbg(stack.size());
    return out;
}

string beam(vector<pair<int, int>> &pos, pair<int, int> init){
    int width = 100;
    string best = naive(pos, init);
    int best_score = eval(best);
    using que_t = priority_queue<pair<int, pair<vector<pii>, pair<pii, string>>>>;
    que_t cands;

    while(cands.size()){
        que_t nexts;

        cands = que_t();
        for(int i=0; i<width; i++){
            if(nexts.empty()) break;
            auto next = nexts.top();
            if(next.second.first.size()==0){
                best_score = next.first;
                best = next.second.second.second;
                break;
            }
            nexts.pop();
            cands.push(next);
        }
    }

    return best;
}

vector<pair<vector<pii>, pair<pii, string>>> next_states(vector<pair<int, int>> &pos, pii init){
    vector<pair<vector<pii>, pair<pii, string>>> states;
    if(pos.size() == 1){
        int dx = pos[0].first-init.first;
        int dy = pos[0].second-init.second;
        string x;
        x += string(abs(dx), dx<0?'U':'D');
        x += string(abs(dy), dy<0?'L':'R');
        x += 'I';

        states.push_back({vector<pii>(), pair<pii, string>(pos[0], x)});
        return states;
    }
    vector<vector<int>> board(20, vector<int>(20, -1));
    for(int i=0; i<pos.size(); i++){
        board[pos[i].first][pos[i].second] = i;
    }

    for(int i=1; i<pos.size(); i++){
        if(pos[i].first<min(pos[0].first, init.first)||max(pos[0].first, init.first)<pos[i].first ||
            pos[i].second<min(pos[0].second, init.second)||max(pos[0].second, init.second)<pos[i].second){
                continue;
        }

        string s;
        int dx = pos[i].first - init.first;
        int dy = pos[i].first - init.second;
        s += string(abs(dx), dx<0?'U':'D');
        s += string(abs(dy), dy<0?'L':'R');
        s += 'I';
        board[pos[i].first][pos[i].second] = -1;

        pii orig = pos[i];

        for(int x=min(pos[i].first, pos[0].first); x<max(pos[i].first, pos[0].first)+1; x++){
            for(int y=min(pos[i].second, pos[0].second); y<max(pos[i].second, pos[i].second)+1; y++){
                
            }
        }


    }

}



int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n = 100;
    vector<pair<int, int>> p(n);
    for(int i=0; i<n; i++){
        int x, y;
        cin >> x >> y;
        p[i].first = x;
        p[i].second = y;
    }

    pair<int, int> now(0, 0);
    string out = align(p, now);

    out += naive(p, now);

    cout << out << endl;
    dbg(eval(out));

    return 0;
}