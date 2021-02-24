const int MAXN = 2e5+5;
int a[MAXN];

void merge(int l, int r){
    vi ord;
    int m = l+r>>1;
    int i=l, j=m+1;
    while(i<=m && j<=r){
        if(a[i] < a[j])
            ord.pb(a[i++]);
        else
            ord.pb(a[j++]);       
    }
    while(i<=m) ord.pb(a[i++]);
    while(j<=r) ord.pb(a[j++]);
    for (i=0; i<sz(ord); i++, l++) a[l] = ord[i];
}


void merge_sort(int l, int r){
    if(l==r) return;
    else{
        int m = l + r >> 1;
        merge_sort(l, m);
        merge_sort(m+1, r);
        merge(l, r);
    }
}