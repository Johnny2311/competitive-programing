#include <bits/stdc++.h>
#define int ll
#define pb push_back
#define sz(v) (int)(v).size()
#define debug(x) cerr << #x << "_=_" << x << "\n";
#define all(v) begin(v), end(v)
#define fst first
#define snd second
using namespace std;
/* https://codeforces.com/gym/312877/problem/F
 * 
 * Counting the number of increasing subsecuences with length K
 * 
 * N <= 1e5
 * K <= 10
 * Ai <= N
 */
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<ii, int> iii;
typedef pair<ll, pll> lll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
const int MOD = 1e9+7;
const ll oo = 1e18;
template<typename num>
inline num ceil(num a, num b){return (a+b-1)/b;} // (a/b)
template<typename num>
inline num lcm(num a, num b){return a*(b/__gcd(a, b));}
//template<typename num>
//inline num sum(num x){return x * (x+1) / 2;}    //sum(1...x)

const int MAXN = 3e5+5;
int a[MAXN], biTree[15][MAXN], dp[MAXN][15];


int sum(int k, int idx) {
    int s = 0;
    while (idx >= 1) {
        s += biTree[k][idx];
        idx ^= idx&-idx;
    }
    return s;
}

void add(int k, int idx, int x) {
    while (idx < MAXN) {
        biTree[k][idx] += x;
        idx += idx&-idx;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    int t = 1;
//    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            dp[i][1] = 1;
        }

        k++;

        ull ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 2; j <= k; ++j) {
                dp[i][j] = sum(j-1, a[i]);
            }

            for (int j = 1; j <= k; ++j) {
                add(j, a[i], dp[i][j]);
            }
            ans += dp[i][k];
        }

        cout << ans << "\n";


    }




    return 0;
}
