#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
#define rep(i,N) for(int i=0;i<int(N);++i)
#define rep1(i,N) for(int i=1;i<int(N);++i)
#define all(a) (a).begin(),(a).end()
#define bit(k) (1LL<<(k))
#define SUM(v) accumulate(all(v), 0LL)

typedef pair<int, int> i_i;
typedef pair<ll, ll> l_l;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
struct fast_ios{ fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; }fast_ios_;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define TOSTRING(x) string(#x)
template <typename T> istream &operator>>(istream &is, vector<T> &vec) { for (T &x : vec) is >> x; return is; }
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) { os  << "["; for(auto _: v) os << _ << ", "; os << "]"; return os; };
template <typename T> ostream &operator<<(ostream &os, set<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T> ostream &operator<<(ostream &os, multiset<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T, typename U> ostream &operator<<(ostream &os, const pair< T, U >& p){os << "{" <<p.first << ", " << p.second << "}";return os; }
template <typename T, typename U> ostream &operator<<(ostream &os, const map<T, U> &mp){ os << "["; for(auto _: mp){ os << _ << ", "; } os << "]" << endl; return os; }

#define DUMPOUT cerr
void dump_func(){ DUMPOUT << endl; }
template <class Head, class... Tail> void dump_func(Head &&head, Tail &&... tail) { DUMPOUT << head; if (sizeof...(Tail) > 0) { DUMPOUT << ", "; } dump_func(std::move(tail)...); }

#ifdef DEBUG
#define dbg(...)  dump_func(__VA_ARGS__) 
#define dump(...) DUMPOUT << string(#__VA_ARGS__) << ": "; dump_func(__VA_ARGS__)
#else
#define dbg(...)
#define dump(...)
#endif

//
constexpr double TL = 2.09;
constexpr long long CYCLES_PER_SEC = 2800000000;
struct MyTimer {
long long start;

MyTimer() { reset(); }

void reset() { start = getCycle(); }

inline double get() { return (double) (getCycle() - start) / CYCLES_PER_SEC; }

inline long long getCycle() {
    unsigned low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((long long) low) | ((long long) high << 32);
}
};
//
const int INF = (ll)1e9;
const ll INFLL = (ll)1e18+1;
const ll MOD = 1000000007;
// const ll MOD = 998244353;
const long double PI = acos(-1.0);

const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

const int cardN = 100;
const int H = 20, W = 20;
int xin[cardN+5], yin[cardN+5];
const int MAXNearCardsNum = 99;
int dist(int ax, int ay, int bx, int by){
    return abs(ax - bx) + abs(ay - by);
}
int dist(const pair<int, int> &a, const pair<int, int> &b){
    return dist(a.first, a.second, b.first, b.second);
}
struct Stage{
    // int stage[H][W];
    vector<vector<int>> stage;
    vvec<int> stage_vec;
    vvec<int> nearCards;
    pair<int,int> revCard[cardN+5];
    int squareNum[H][W];
    pair<int, int> revSquare[H*W];
    string dir = "DRUL";
    Stage(){
        stage.resize(H);
        rep(i,H)stage[i].resize(W);
        rep(i,H)rep(j,W)stage[i][j] = -1;
        rep(i,cardN)revCard[i] = {-1, -1};
        stage_vec.resize(H);
        setSquareNum();
    }
    pair<int, int> getCardPos(const int idx){
        if(idx == cardN)return {0, 0};
        return revCard[idx];
    }
    pair<int, int> getSquarePos(const int idx){
        if(idx == cardN)return {0, 0};
        return revSquare[idx];
    }
    void setNearCards(){
        nearCards.resize(cardN+5);
        rep(i,cardN+1){
            bfs(i);
        }
    }
    bool IsIn(int i,int j){
        return 0 <= i && i < H && 0 <= j && j < W;
    }
    void bfs(const int startCardIdx){
        queue<pair<pair<int, int>, int>> q;
        bool visited[H+5][W+5];
        rep(i,H)rep(j,W)visited[i][j] = false;
        auto [xx, yy] = getCardPos(startCardIdx);
        q.push({getCardPos(startCardIdx), startCardIdx});
        visited[xx][yy] = true;
        while(nearCards[startCardIdx].size() < MAXNearCardsNum){
            auto pp = q.front();
            auto [x, y] = pp.first;
            auto idx = pp.second;
            q.pop();
            rep(k,4){
                int nx = x + dx[k];
                int ny = y + dy[k];
                int nidx = stage[nx][ny];
                if(visited[nx][ny])continue;
                if(not IsIn(nx, ny))continue;
                if(isExist(nx, ny)){
                    nearCards[startCardIdx].emplace_back(stage[nx][ny]);
                }
                visited[nx][ny] = true;
                q.push({{nx, ny}, nidx});
            }
        }
    }
    void setSquareNum(){
        int cnt = 0;
        rep(i,H/2){
            if(i&1){
                for(int j = W/2-1; j >= 0; j--){
                    squareNum[i][j] = cnt;
                    revSquare[cnt] = {i,j};
                    cnt++;
                }
            }
            else{
                rep(j,W/2){
                    squareNum[i][j] = cnt;
                    revSquare[cnt] = {i,j};
                    cnt++;
                }
            }
        }
    }
    void setCard(int x, int y, int Num){
        stage[x][y] = Num;
        stage_vec[x].push_back(y);
        revCard[Num] = {x, y};
    }
    void sortvec(){
        rep(i,H)sort(all(stage_vec[i]));
    }
    bool isExist(int x, int y){
        return stage[x][y] != -1;
    }
    void Rotate(bool isDebug = false){
        auto tmpstage = stage;
        auto tmpdir = dir;
        rep(i,4){
            if(tmpdir[i] == 'L')dir[i] = 'U';
            if(tmpdir[i] == 'D')dir[i] = 'L';
            if(tmpdir[i] == 'R')dir[i] = 'D';
            if(tmpdir[i] == 'U')dir[i] = 'R';
        }
        rep(i,H){
            rep(j,W){
                int cx = H-1-j;
                int cy = i;
                stage[cx][cy] = tmpstage[i][j];
            }
        }
        if(isDebug){
            rep(i,H){
                dbg(tmpstage[i]);
            }
            DUMPOUT << endl;
            rep(i,H){
                dbg(stage[i]);
            }
            dbg(tmpdir);
            dbg(dir);
        }
    }
    // void Rotate() {
    //     for (int i = 1; i <= N; i++) {
    //         int cx = Y[i], cy = 200000 - X[i], cz;
    //         if (D[i] == 'U') cz = 'R';
    //         if (D[i] == 'R') cz = 'D';
    //         if (D[i] == 'D') cz = 'L';
    //         if (D[i] == 'L') cz = 'U';
    //         X[i] = cx; Y[i] = cy; D[i] = cz;
    //     }
    // }
    void dumpCard(){
        rep(i,H){
            rep(j,W){
                DUMPOUT << stage[i][j] << " ";
            }
            DUMPOUT << endl;
        }
    }
    void dumpNearCards(){
        rep(i,cardN+1){
            dump(i, nearCards[i]);
        }
    }
    void dumpsquareNum(){
        DUMPOUT << "squareNum" << endl;
        rep(i,H){
            rep(j,W){
                DUMPOUT << squareNum[i][j] << " ";
            }
            DUMPOUT << endl;
        }
        DUMPOUT << "revSquare" << endl;
        rep(i,H*W){
            DUMPOUT << revSquare[i] << " ";
        }
        DUMPOUT << endl;
    }
};
Stage aStage;
struct Player{
    int nowx, nowy;
    int lastx, lasty;
    vector<int> tehuda;
    string ansStr;
    int cost = 4000;
    Player(){
        nowx = 0, nowy = 0;
        cost = 4000;
    }
    void nameru(){
        rep(i,H){
            if(i&1){
                for(int j = W-1; j >= 0; j--){
                    goIn(i, j);
                }
            }
            else{
                rep(j,W){
                    goIn(i, j);
                }
            }
        }
    }
    void nameru_short(){
        rep(i,H){
            int w_sz = aStage.stage_vec[i].size();
            if(i&1){
                for(int j = w_sz-1; j >= 0; j--){
                    goIn(i, aStage.stage_vec[i][j]);
                }
            }
            else{
                rep(j,w_sz){
                    goIn(i, aStage.stage_vec[i][j]);
                }
            }
        }
    }
    // カードの順序が与えられるので、その順番に回収してください
    void getCardbySeq(const vector<int>& seq){
        assert(seq.size() == cardN+1);
        assert(seq[0] == cardN);
        for(int i = 1; i <= cardN; i++){
            goIn(aStage.getCardPos(seq[i]));
        }
        return;
    }
    void goIn(const pair<int, int>& p){
        goIn(p.first, p.second);
    }
    void goIn(const int i, const int j){
        goPos(i, j);
        cardIn();
    }
    void goOut(const int i, const int j){
        goPos(i, j);
        cardOut();
    }
    void cardIn(){
        if(not aStage.isExist(nowx, nowy))return;
        addCommand('I');
        tehuda.push_back(aStage.stage[nowx][nowy]);
        aStage.stage[nowx][nowy] = -1;
    }
    void cardOut(){
        if(aStage.isExist(nowx, nowy))return;
        if(tehuda.empty())return;
        addCommand('O');
        aStage.stage[nowx][nowy] = tehuda.back();
        tehuda.pop_back();
    }
    void goPos(int nxtx, int nxty){
        int nowdist = dist(nowx, nowy, nxtx, nxty);
        while(nowdist > 0){
            rep(i,4){
                int nxtdist = dist(nowx + dx[i], nowy + dy[i], nxtx, nxty);
                if(chmin(nowdist, nxtdist)){
                    nowx += dx[i];
                    nowy += dy[i];
                    addCommand(aStage.dir[i]);
                }
            }
        }
    }
    void addCommand(char c){
        ansStr.push_back(c);
        if(c != 'I' && c != 'O')cost--;
    }
    int dist(int ax, int ay, int bx, int by){
        return abs(ax - bx) + abs(ay - by);
    }
    void Rotate(bool isDebug = false){
        int tmp_nowx = nowx;
        int tmp_nowy = nowy;
        nowx = H-1-tmp_nowy;
        nowy = tmp_nowx;
        lastx = nowx;
        lasty = nowy;
        if(isDebug){
            dump(tmp_nowx, tmp_nowy);
            dump(nowx, nowy);
        }
    }
    void hidariUekaraOkuAfterRotate(bool isDebug = false){
        while(not tehuda.empty()){
            int cardNum = tehuda.back();
            auto [targetX, targetY] = aStage.revSquare[cardNum];
            targetX += lastx;
            targetY += lasty;
            goOut(targetX, targetY);
        }
        if(isDebug){
            aStage.dumpCard();
            DUMPOUT << endl;
        }
    }
    void hidariUekaraToruAfterRotate(bool isDebug = false){
        rep(i,H/2){
            if(i&1){
                for(int j = W/2-1; j >= 0; j--){
                    goIn(lastx + i,lasty + j);
                }
            }
            else{
                rep(j,W/2){
                    goIn(lastx + i, lasty + j);
                }
            }
        }
        if(isDebug){
            aStage.dumpCard();
            DUMPOUT << endl;
        }
    }
    void hidariUekaraOku(bool isDebug = false){
        while(not tehuda.empty()){
            int cardNum = tehuda.back();
            auto [targetX, targetY] = aStage.revSquare[cardNum];
            goOut(targetX, targetY);
        }
        if(isDebug){
            aStage.dumpCard();
        }
    }
    void hidariUekaraToru(){
        rep(i,H/2){
            if(i&1){
                for(int j = W/2-1; j >= 0; j--){
                    goIn(i,j);
                }
            }
            else{
                rep(j,W/2){
                    goIn(i, j);
                }
            }
        }
    }
    void Guchoku(){
        rep(i,cardN){
            auto [x, y] = aStage.revCard[i];
            goIn(x, y);
        }
    }
};
Player aPlayer;
struct CardTour{
    vector<int> seq;
    vector<bool> used;
    int cost;
    CardTour(){
        cost = 0;
        used.assign(cardN+5,false);
        seq.emplace_back(cardN);
    }
    void add2Seq(const int idx){
        seq.emplace_back(idx);
        used[idx] = true;
        return;
    }
    void pushCard(const int idx){
        // if(seq.empty()){
        //     cost += dist(make_pair(0,0), aStage.getCardPos(idx));
        //     cost += dist(make_pair(0,0), aStage.getSquarePos(idx));
        //     add2Seq(idx);
        //     return;
        // }
        int preidx = seq.back();
        cost += dist(aStage.getCardPos(preidx), aStage.getCardPos(idx));
        cost += dist(aStage.getSquarePos(preidx), aStage.getSquarePos(idx));
        add2Seq(idx);
        // 今入れたのが最後である場合
        // if(seq.size() == cardN+1){
        //     cost += dist(aStage.getCardPos(idx), aStage.getSquarePos(idx));
        // }
    }
    bool operator<(const CardTour& b) const{
        return (*this).cost > b.cost;
    }

};
void dump_ques(const vector<priority_queue<CardTour>> & a){
    for(auto x: a){
        DUMPOUT << x.size() << " ";
    }
    DUMPOUT << endl;
}
CardTour chokudai_search(const int& n_itr, const int& chokudai_width = 1, bool isDump = false){
    vector<priority_queue<CardTour>> ques(cardN+1);
    ques[0].push(CardTour()); // デフォルトのやつを挿入 初期位置のみ入ってる
    rep(_, n_itr){
        if(isDump && _%20 == 0){
            dump(_);
            dump_ques(ques);
        }
        for(int depth = 0; depth < cardN; depth++){
            auto &que = ques[depth];
            auto &nxt_que = ques[depth + 1];
            for(int i = 0; i < chokudai_width; i++){
                if(que.empty())break;
                auto state = que.top(); que.pop();
                int from = state.seq.back(); // ここから出発 -> あらかじめbfsかなんかで近傍の20枚くらいを列挙しておこうStage内で -> できた
                // int cnt = 0;
                for(int idx: aStage.nearCards[from]){
                    // if(cnt > 5)break;
                    if(not state.used[idx]){
                        auto nxt_state = state;
                        nxt_state.pushCard(idx);
                        nxt_que.push(nxt_state);
                        // cnt++;
                    }
                }
            }
        }
    }
    assert(not ques[cardN].empty());
    CardTour res = ques[cardN].top();
    dump(res.seq);
    return res;
}
void RotateForPut(){
    int cnt = 0;
    if(0 <= aPlayer.nowx && aPlayer.nowx < H/2){
        if(0 <= aPlayer.nowy && aPlayer.nowy < W/2){
            cnt = 0;
        }
        else{
            cnt = 1;
        }
    }
    else{
        if(0 <= aPlayer.nowy && aPlayer.nowy < W/2){
            cnt = 3;
        }
        else{
            cnt = 2;
        }
    }
    while(cnt--){
        aStage.Rotate();
        aPlayer.Rotate();
    }
}
void input(){
    rep(i,cardN){
        cin >> xin[i] >> yin[i];
        aStage.setCard(xin[i], yin[i], i);
    }
    aStage.sortvec();
    aStage.setNearCards();
}
void solve_NameteOku(){
    aPlayer.nameru();
    aPlayer.hidariUekaraOku();
    aPlayer.hidariUekaraToru();
}
void solve_NameteOku_short(){
    aPlayer.nameru_short();
    aPlayer.hidariUekaraOku();
    aPlayer.hidariUekaraToru();
}
void solve_Guchoku(){
    aPlayer.Guchoku();
}
void solve_chokudai(){
    // 順番を決めて
    CardTour best_state = chokudai_search(500, 1);
    dump(best_state.seq);
    
    aPlayer.getCardbySeq(best_state.seq);
    // ここまで決まったら、いる位置によって回転する回数を決める
    RotateForPut(); // 
    aPlayer.hidariUekaraOkuAfterRotate();
    aPlayer.hidariUekaraToruAfterRotate();
    // aPlayer.hidariUekaraOku();
    // aPlayer.hidariUekaraToru();
}
int main() {
    MyTimer timer;
    timer.reset();
    input();
    solve_chokudai();
    cout << aPlayer.ansStr << endl;
    dump(aPlayer.cost);
    dump(timer.get());
}

// 最後に終了したところから、{0,0}に戻る時間が無駄なので、上下左右にスタートして10 * 10の盤面が形成できる方向を調べ、そこに升目を展開する