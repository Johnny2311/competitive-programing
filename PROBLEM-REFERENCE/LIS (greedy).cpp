 
const int MAXN = 2e5+5;
int a[MAXN];


//main
vector<int> L;
L.push_back(a[0]);
for (int i = 1; i < n; ++i) {
    auto it = lower_bound(L.begin(), L.end(), a[i]);
    if (it == L.end())
        L.push_back(a[i]);
    else
        *it = a[i];
}

//sz(L) = size of the LIS
    
    
