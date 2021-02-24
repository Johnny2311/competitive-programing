const int MAXN = 2e5+5; LOG = 22;
int a[MAXN], spT[MAXN][LOG];

int rmq(int l, int r) {
    int k = logg[r - l + 1];
    if (a[spT[l][k]] <= a[spT[r - (1 << k) + 1][k]])
        return spT[l][k];
    return spT[r - (1 << k) + 1][k];
}

//..main

    logg[1] = 0;
    for (int i = 2; i < MAXN; i++)  //precompute logaritms
        logg[i] = logg[i/2] + 1;
    
    for (int i = 0; i < n; ++i)
        spT[i][0] = i;
    
    for (int k = 1; (1<<k) <= n; ++k) {
        for (int i = 0; i + (1<<k) <= n; ++i) {
            if (a[spT[i][k-1]] <= a[spT[i+(1<<(k-1))][k-1]])    //save the idx instead the number
                spT[i][k] = spT[i][k-1];
            else
                spT[i][k] = spT[i+(1<<(k-1))][k-1];
        }
    }
