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

constexpr double TL = 2.95;
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

class Solver{
public:
    string ans;
    set<pair<int,int>> movedFields;
    int fieldSize;
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
        while(aMyTimer.get() < TL && movedFields.size() < fieldSize) {
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
        cnt[i][j]++;
        rep(k,4){
            int x = i + dx[k];
            int y = j + dy[k];
            while(isInField(x, y) && !isWall(x, y)) {
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
        rep(k,4){
            int ni = i + dx[k];
            int nj = j + dy[k];
            if(!isInField(ni, nj) || !isWall(ni,nj)) {
                res++;
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
        dump(x, y, dirIdx, dir[dirIdx]);
        ans.push_back(dir[dirIdx]);
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
