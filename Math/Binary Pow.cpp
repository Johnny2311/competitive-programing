ll binpow (ll b, ll e) {
    ll res = 1;
    while (e)
        if (e & 1)
            res = (res * b % MOD), --e;
        else
            b = (b * b % MOD), e >>= 1;
    return res;
} 
