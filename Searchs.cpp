 
int ternary_search(int l, int r) {
    int eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        int f1 = f(m1);      //evaluates the function at m1
        int f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                    //return the maximum of f(x) in [l, r]
}

int lower_bound(int k) {
    int l=0, r = n-1;
    while(l <= r) {
        int mid = l + r >> 1;
        if (a[l] < k) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return l-1;
}

int upper_bound(int k) {
    int l=0, r = n-1;
    while(l <= r) {
        int mid = l + r >> 1;
        if (a[l] <= k) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return l-1;
}
