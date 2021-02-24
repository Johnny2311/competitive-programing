/* 
 * Calculate the minimum among all farest nodes in a tree
 *
 *
 */ 
#include <bits/stdc++.h>
#define int ll
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
typedef pair<ii, int> iii;
typedef pair<ll, pll> lll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
const int MOD = 1e9+7;
const ll oo = 1e9;
template<typename num>
inline num ceil(num a, num b){return (a+b-1)/b;} // (a/b)
template<typename num>
inline num lcm(num a, num b){return a*(b/__gcd(a, b));}
//template<typename num>
//inline num sum(num x){return x * (x+1) / 2;}    //sum(1...x)

const int MAXN = 2e5+5;

vvi tree;

vii mx1, mx2;
void dfs(int u, int p=-1) {
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
        if (mx1[v].fst + 1 > mx1[u].fst) {
            mx2[u] = mx1[u];
            mx1[u] = {mx1[v].fst + 1, v};
        }
        else if (mx1[v].fst + 1 > mx2[u].fst){
            mx2[u] = {mx1[v].fst + 1, v};
        }
    }
}

int ans;
void solve(int u, int p=-1) {
    int tmp = 0;
    for (int v : tree[u]) {
        tmp = max(tmp, mx1[v].fst + 1);
    }
    ans = min(ans, tmp);

    for (int v : tree[u]) {
        if (v == p) continue;
        ii x = mx1[u], y = mx1[v], z = mx2[v];
        if (mx1[u].snd == v)
            mx1[u] = mx2[u];
        if (mx1[u].fst + 1 > mx1[v].fst) {
            mx2[v] = mx1[v];
            mx1[v] = {mx1[u].fst, u};
        }
        else if (mx1[u].fst + 1 > mx2[v].fst) {
            mx2[v] = {mx1[u].fst + 1, u};
        }
        solve(v, u);
        mx1[u] = x;
        mx1[v] = y;
        mx2[v] = z;
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
    cin >> t;
    for (int _t = 1; _t <= t; ++_t) {
        int n;
        cin >> n;
        ans = oo;
        mx1.assign(n+1, {0, 0});
        mx2.assign(n+1, {0, 0});
        tree.assign(n+1, vi());
        for (int i = 0, u, v; i < n-1; ++i) {
            cin >> u >> v;
            u++, v++;
            tree[u].pb(v);
            tree[v].pb(u);
        }

        dfs(1);
        solve(1);

        cout << ans << "\n";


    }


    return 0;
}
