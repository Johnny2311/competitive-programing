/*
 * https://vjudge.net/problem/LightOJ-1397
 * https://vjudge.net/problem/LightOJ-1397/origin
 * Sudoku Solver
 */

#include <bits/stdc++.h>
#define pb push_back
#define sz(v) (int)(v).size()
#define debug(x) cerr << #x << "_=_" << x << "\n";
#define all(v) begin(v), end(v)
#define fst first
#define snd second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<int, ii> iii;
typedef pair<ll, pll> lll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
const int MOD = 1e6+3;
const int oo = 1e9;
template<typename num>
inline num ceil(num a, num b){return (a+b-1)/b;} // (a/b)
template<typename num>
inline num lcm(num a, num b){return a*(b/__gcd(a, b));}
template<typename num>
inline num sum(num x){return x * (x+1) / 2;}    //sum(1...x)

//#define int ll
int row[10], col[10], blk[10], cnt[10];

char sudoku[10][10];

bool find_best(int &x, int &y) {
    int mn = oo;
    vi count(81);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudoku[i][j] != '.') continue;
            int b = (i/3) * 3 + (j/3);
            int idx = i * 9 + j;
            for (int k = 1; k <= 9; ++k) {
                if (((row[i] | col[j] | blk[b]) & (1<<k)) == 0) {
                    count[idx]++;
                }
            }
            if (count[idx] < mn) {
                mn = count[idx];
                x = i, y = j;
            }
        }
    }
    return mn != oo;
}

bool fill() {
    int x=-1, y=-1;
    if (!find_best(x, y))
        return true;

    for (int i=1; i<=9; i++) {
        int b = (x/3) * 3 + (y/3);
        if (cnt[i] == 9) continue;
        if (((row[x] | col[y] | blk[b]) & (1<<i)) == 0) {
            row[x] ^= (1<<i);
            col[y] ^= (1<<i);
            blk[b] ^= (1<<i);
            cnt[i]++;
            sudoku[x][y] = '0' + (char)i;
            if (fill())
                return true;
            sudoku[x][y] = '.';
            cnt[i]--;
            blk[b] ^= (1<<i);
            col[y] ^= (1<<i);
            row[x] ^= (1<<i);
        }
    }

    return false;
}

int32_t main()
{

    int t;
    scanf("%d", &t);
    for (int _t = 1; _t <= t; ++_t) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(blk, 0, sizeof blk);
        memset(cnt, 0, sizeof cnt);

        for (int i = 0; i < 9; ++i) {
            scanf("%s", sudoku[i]);
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (sudoku[i][j] != '.') {
                    int d = sudoku[i][j] - '0';
                    cnt[d]++;
                    int b = (i/3) * 3 + (j/3);
                    row[i] ^= (1<<d);
                    col[j] ^= (1<<d);
                    blk[b] ^= (1<<d);
                }
            }
        }

        fill();

        printf("Case %d:\n", _t);
        for (int k = 0; k < 9; ++k) {
            printf("%s\n", sudoku[k]);
        }

    }



    return 0;
}
