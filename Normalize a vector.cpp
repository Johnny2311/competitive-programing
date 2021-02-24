 
//Option 1
vi normalize(vi a) {
    vi _a(a), idx(sz(a));
    sort(all(_a));
    _a.erase(unique(all(_a)), _a.end());
    for(int i = 0; i < sz(a); ++i) {
        idx[i] = lower_bound(all(_a), a[i]) - _a.begin();
    }
    return idx;
}

//Option 2 (for mantain repeted values with diferents idx[i])
vi normalize(vi a) {
    vi idx(sz(a));
    vii _a;
    for (int i = 0; i < sz(a); ++i) _a.pb({a[i], i});
    sort(all(_a));
    for(int i = 0; i < sz(a); ++i) idx[_a[i].snd] = i;
    return idx;
}
