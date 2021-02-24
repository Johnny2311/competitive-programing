 
const int MAXN = 2e5+5;
int a[MAXN], dp[MAXN], idx[MAXN];

//main
//idx = normalize(a)
int ans = 0;
for (int i = 0; i < n; ++i) {
    dp[i] = query(0, idx[i]-1, 1, 0, n-1) + 1;
    ans = max(ans, dp[i]);
    update(idx[i], dp[i], 1, 0, n-1);
}
