 
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
typedef pair<ii, int> iii;
typedef pair<ll, pll> lll;
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
inline num sum(num x){return x * (x+1) / 2;}    //sum(1...x)

//#define int ll
#define x fst.fst
#define y fst.snd
#define idx snd
const int MAXN = 5e4+5;
iii a[MAXN];

int32_t main()
{
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    int t = 1;
//    cin >> t;
    while(t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d" , &a[i].x, &a[i].y);
            a[i].idx = i;
        }

        sort(a, a+n);

        double ans = oo;
        int l=-1, r=-1;
        set<iii> s;
        for (int i = 0, j = 0; i < n; ++i) {
            while(a[i].x - a[j].x > ans)
                s.erase({{a[j].y, a[j].x}, a[j].idx}), ++j;

            auto start = s.lower_bound({{a[i].y - ans, -oo}, -oo});
            auto end = s.upper_bound({{a[i].y + ans, -oo}, -oo});
            for (auto it = start; it != end; ++it) {
                double d = hypot(a[i].x - it->y, a[i].y - it->x);
                if (d < ans) {
                    ans = d;
                    l = it->idx;
                    r = a[i].idx;
                }
            }
            s.insert({{a[i].y, a[i].x}, a[i].idx});
        }

        printf("%d %d %.6lf\n", min(l, r), max(l, r), ans);
    }


    return 0;
}
