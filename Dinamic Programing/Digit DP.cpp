/* Solution 1 */
int dp[15][2][105], check[15][2][105];   //if dont use check have to reset dp when num change
int _t;   //current test case              

string num;
int f(int pos, int v, int sum){     //call f(sz(num), 1, k)
    if(pos == 0) return sum==0;
    if(check[pos][v][sum] == _t || (check[pos][v][sum] && v==0))    //trick to speed up
        return dp[pos][v][sum];
    int ans=0, cur = num[sz(num)-pos]-'0';
    int d = (v ? cur : 10);
    for (int i=0; i<d; i++)
        if(sum-i>=0)
            ans += f(pos-1, 0, sum-i);
    if(v && sum-cur>=0)
        ans += f(pos-1, 1, sum-cur);
    check[pos][v][sum] = _t;
    return dp[pos][v][sum] = ans;
}

/* Solution 2 */ 
int dp[15][105];

int f(int cnt, int sum){
    if(cnt==0) return sum==0;
    if(~dp[cnt][sum])
        return dp[cnt][sum];
    int ans=0;
    for (int i=0; i<10; i++)
        if(sum-i>=0)
            ans += f(cnt-1, sum-i);
    return dp[cnt][sum] = ans;
}

int solve(int n, int k){
    string num = to_string(n);
    int ans = 0, sum = k;
    int len = sz(num);
    int remain = len;
    for (int i=0; i<len; i++){
        remain--;
        int d = num[i]-'0';
        for (int j=0; j<d; j++){
            if(sum-j>=0)                    //sum-j = property'
                ans += f(remain, sum-j);
        }
        sum -= d;                           //update property
    }
    return ans;
}