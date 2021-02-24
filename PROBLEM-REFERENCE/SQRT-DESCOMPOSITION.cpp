/*
 * https://codeforces.com/problemset/problem/455/D
 * - Serega and fun 
 * 
 * 
 * */


#include <bits/stdc++.h>
#define pb push_back
#define sz(v) (int)(v).size()
#define debug(x) cerr << #x << "_=_" << x << "\n";
#define all(v) begin(v), end(v)
#define fst first
#define snd second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<pair<int, int>, int> iii;
typedef pair<pair<ll, ll>, ll> lll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
const int MOD = 998244353;
const int oo = 1e9;
template<typename num>
inline num ceil(num a, num b){return (a+b-1)/b;} // (a/b)
template<typename num>
inline num lcm(num a, num b){return a*(b/__gcd(a, b));}
template<typename num>
inline num sum(num x){return x * (x+1) / 2;}

const int MAXN = 2e5+5, MAXBLK = 320;
int a[MAXN];
short cnt[MAXBLK][MAXN];
vi block[MAXBLK];
int n, sz_bck;

void build() {
    int cur_blk = -1;
    for (int i = 0; i < n; ++i) {
        if (i%sz_bck==0) cur_blk++;
        block[cur_blk].pb(a[i]);
        cnt[cur_blk][a[i]]++;
    }
}

void rebuild() {
    int cur_blk = 0;
    for (int i = 0; i < n; ) {
        for (int j = 0; j < sz(block[cur_blk]); ++i, ++j) {
            a[i] = block[cur_blk][j];   ///rebuild array a[]
            cnt[cur_blk][a[i]]--;       ///clean array cnt[][]
        }
        block[cur_blk].clear();         ///clean blocks
        cur_blk++;
    }
    build();                            ///rebuild the whole structure
}

void shift(int l, int r) {
    int cur_blk = 0;
    while (r >= sz(block[cur_blk])) {
        r -= sz(block[cur_blk]);
        ++cur_blk;
    }
    int elem = block[cur_blk][r];
    block[cur_blk].erase(begin(block[cur_blk]) + r);
    cnt[cur_blk][elem]--;

    cur_blk = 0;
    while (l >= sz(block[cur_blk])) {
        l -= sz(block[cur_blk]);
        ++cur_blk;
    }
    block[cur_blk].insert(begin(block[cur_blk]) + l, elem);
    cnt[cur_blk][elem]++;
}

int query(int l, int r, int k) {
    int cur_blk = 0;
    int range = r - l + 1;
    while (l >= sz(block[cur_blk])) {
        l -= sz(block[cur_blk]);
        ++cur_blk;
    }
    int ans = 0;
    while (l < sz(block[cur_blk]) && range) {
        ans += block[cur_blk][l] == k;
        ++l, --range;
    }
    ++cur_blk;
    while (sz(block[cur_blk]) <= range && range) {
        ans += cnt[cur_blk][k];
        range -= sz(block[cur_blk]);
        ++cur_blk;
    }
    while(range) {
        ans += block[cur_blk][range-1] == k;
        --range;
    }
    return ans;
}

void debug_blocks() {
    int cur_blk = 0;
    for (int i = 0; i < n; ) {
        cerr << "[ ";
        for (int j = 0; j < sz(block[cur_blk]); ++i, ++j) {
            cerr << block[cur_blk][j] << " ";
        }
        cerr << "] ";
        ++cur_blk;
    }
    cerr << "\n";
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> n;
    sz_bck = sqrt(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    build();

    int q, type1 = 0, ans=0;
    cin >> q;
    while(q--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        l = (l + ans - 1) % n + 1;
        r = (r + ans - 1) % n + 1;
        --l, --r;
        if (l > r) swap(l, r);
        if (op == 1) {
//            debug_blocks();
            if (l != r)
                shift(l, r);
            type1++;
        }
        else {
            cin >> k;
            k = (k + ans - 1) % n + 1;
            ans = query(l, r, k);
            cout << ans << "\n";
        }
        if (type1 == sz_bck) {
            rebuild();
            type1 = 0;
        }
    }
//    debug_blocks();

    return 0;
}
