#include <bits/stdc++.h>
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
template <typename T, typename U> ostream &operator<<(ostream &os, const map<T, U> &mp){ os << "["; for(auto _: mp){ os << _ << ", "; } os << "]"; return os; }

#define DUMPOUT cerr
void dump_func(){ DUMPOUT << endl; }
template <class Head, class... Tail> void dump_func(Head &&head, Tail &&... tail) { DUMPOUT << head; if (sizeof...(Tail) > 0) { DUMPOUT << ", "; } dump_func(std::move(tail)...); }

#ifdef DEBUG
#define dbg(...) { dump_func(__VA_ARGS__) }
#define dump(...) DUMPOUT << string(#__VA_ARGS__) << ": "; dump_func(__VA_ARGS__)
#else
#define dbg(...)
#define dump(...)
#endif

const int INF = (ll)1e9;
const ll INFLL = (ll)1e18+1;
const ll MOD = 1000000007;
// const ll MOD = 998244353;
const long double PI = acos(-1.0);

const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const string dir = "DRUL";

uint32_t XorShift(void) {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;
 
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

constexpr double TL = 2.7;
long long CYCLES_PER_SEC = 2800000000;
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
}aMyTimer;

constexpr int maxN = 100;
int N;
int si, sj; // start grid
char field[maxN][maxN];
int cnt[maxN][maxN];
int surround[maxN][maxN];

int f(int i, int j){
    return i * N + j;
}

pair<int, int> finv(int X){
    return make_pair(X / N, X % N);
}
template<class T> class Dijkstra {
public:
    int N;
    T inf;
    vector<T> cost;
    vector<int> prev;
    vector<vector<pair<T, int>>> edge;

    Dijkstra(){}
    Dijkstra(const int _N, T _inf) : N(_N), inf(_inf),cost(_N), edge(_N), prev(_N,-1) {
    }

    void init(const int _N, T _inf) {
        N = _N;
        inf = _inf;
        cost.resize(_N);
        edge.resize(_N);
        prev.assign(_N, -1);
    }
 
    void make_edge(int from, int to, T w) {
        edge[from].push_back({ w,to });
    }
 
    void solve(int start) {
        for(int i = 0; i < N; ++i) cost[i] = inf;

        dump(start);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        cost[start] = 0;
        pq.push({ 0,start });
 
        while (!pq.empty()) {
            T v = pq.top().first;
            int from = pq.top().second;
            pq.pop();
            for (auto u : edge[from]) {
                T w = v + u.first;
                int to = u.second;
                if (w < cost[to]) {
                    cost[to] = w;
                    prev[to] = from;
                    pq.push({ w,to });
                }
            }
        }
        return;
    }

    vector<int> get_path(int t){ //頂点tへの最短路
        vector<int> path;
        for(; t != -1;t=prev[t]){
            path.push_back(t);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    string get_path_string(int t) {
        vector<int> path = get_path(t);
        int sz = path.size();
        string pathString;
        rep(i,sz-1){
            auto [x, y] = finv(path[i]);
            auto [nx, ny] = finv(path[i+1]);
            rep(k,4){
                if(nx-x == dx[k] && ny-y == dy[k]){
                    pathString.push_back(dir[k]);
                }
            }
        }
        return pathString;
    }
};

class Solver{
public:
    string ans;
    set<pair<int,int>> movedFields;
    int fieldSize;
    Dijkstra<int> G;
    void input(){
        cin >> N;
        cin >> si >> sj;
        rep(i,N)rep(j,N){
            cin >> field[i][j];
        }
    }

    void init(){
        rep(i,N)rep(j,N){
            cnt[i][j] = 0;
            surround[i][j] = 0;
            if(!isWall(i,j))fieldSize++;
        }
        calcSurrounds();

        // Dijkstra Init
        G.init(N*N, INF);
        rep(i,N)rep(j,N){
            if(isWall(i, j))continue;
            rep(k,4){
                int ni = i + dx[k];
                int nj = j + dy[k];
                if(isWall(ni, nj))continue;
                if(not isInField(ni, nj))continue;
                G.make_edge(f(i,j), f(ni,nj), field[ni][nj]-'0');
            }
        }
    }

    void ouput(){
        cout << ans << endl;
    }

    void randomSolve(){
        // ansを更新するだけ
        int x = si;
        int y = sj;
        movedFields.insert({x, y});
        int preDirIdx = 0;
        int itr = 0;
        while(aMyTimer.get() < TL) {
            if(movedFields.size() == fieldSize)break;
            itr++;
            vector<int> kouhoDirIdxs;
            bool isSurround = false;
            rep(k,4){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(isWall(nx, ny))continue;
                if(!isInField(nx, ny))continue;
                if(k == invDir(preDirIdx))continue;
                if(getSurround(nx, ny) - getSurround(x, y) > 0) {
                    move(x, y, k);
                    preDirIdx = k;
                    isSurround = true;
                    break;
                }
                kouhoDirIdxs.push_back(k);
            }
            if(isSurround)continue;
            int sz = kouhoDirIdxs.size();
            if(sz == 0){
                int dirIdx = invDir(preDirIdx);
                move(x, y, dirIdx);
                preDirIdx = dirIdx;
                continue;
            }
            int dirIdx = kouhoDirIdxs[XorShift()%sz];
            move(x, y, dirIdx);
            preDirIdx = dirIdx;
        }

        // 帰る
        dump(x, y);
        G.solve(f(x, y));
        string path = G.get_path_string(f(si, sj));
        ans += path;
    }

    void dumpSurround(){
        rep(i,N){
            rep(j,N){
                cerr << surround[i][j] << " ";
            }
            cerr << endl;
        }
    }

private:
    /*
    ある座標に到達したときに、cnt盤面を更新する関数
    */
    void viewCalc(int i, int j) {
        if(getSurround(i,j) == 0)return;
        cnt[i][j]++;
        movedFields.insert({i,j});
        rep(k,4){
            int x = i + dx[k];
            int y = j + dy[k];
            while(isInField(x, y) && !isWall(x, y)) {
                movedFields.insert({x,y});
                cnt[x][y]++;
                x = x + dx[k];
                y = y + dy[k];
            }
        }
    }

    bool isInField (int i,int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    };

    bool isWall (int i,int j) {
        return field[i][j] == '#';
    };

    void calcSurrounds(){
        rep(i,N)rep(j,N){
            surround[i][j] = _calcSurround(i, j);
        }
    }

    int _calcSurround(int i, int j) {
        int res = 0;
        if(isWall(i, j))return res;
        rep(k,4){
            int ni = i + dx[k];
            int nj = j + dy[k];
            int mi = i + dx[(k+1)%4];
            int mj = j + dy[(k+1)%4];
            if(isInField(ni, nj) && !isWall(ni,nj)) {
                if(isInField(mi, mj) && !isWall(mi,mj)) {
                    res++;
                }
            }
        }
        return res;
    }

    int getSurround(int i, int j){
        return surround[i][j];
    }
    
    void move(int &x, int &y, int dirIdx) {
        x = x + dx[dirIdx];
        y = y + dy[dirIdx];
        movedFields.insert({x, y});
        // dump(x, y, dirIdx, dir[dirIdx]);
        ans.push_back(dir[dirIdx]);
        if(movedFields.find({x, y}) == movedFields.end()){
            viewCalc(x, y);
        }
    }

    int invDir(int dirIdx) {
        return ((dirIdx - 2)+4)%4;
    }
};


int main() {
    aMyTimer.reset();

    Solver aSolver;
    aSolver.input();
    aSolver.init();

    // write your own algorithm!!!!
    int itr = 0;
    aSolver.randomSolve();
    while(aMyTimer.get() < TL/2){
    }
    dump(si, sj, aSolver.movedFields);
    aSolver.ouput();

    // dump
    // aSolver.dumpSurround();

}
