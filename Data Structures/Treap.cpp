typedef struct item * pitem;
struct item {
    int key, prior, cnt;
    pitem l, r;
    item() { }
    item (int key) : key(key), prior(rand()), l(nullptr), r(nullptr) { }
};

int cnt (pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
    if (t)
        t->cnt = 1 + cnt(t->l) + cnt (t->r);
}

//l <= key < r
void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = nullptr;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd_cnt(t);
}

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt(t);
}

void erase (pitem & t, int key) {
    if (t->key == key)
        merge (t, t->l, t->r);
    else
        erase (key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}

int search (pitem t, int val, int idx=0) {
    if (!t) return -1;
    if (val == t->key)
        return idx + cnt(t->l);
    else if (val < t->key)
        return search(t->l, val, idx);
    else
        return search(t->r, val, idx + 1 + cnt(t->l));
}

int kth_element (pitem t, int k) {
    if (!t) return -1;
    int cur_key = cnt(t->l) + 1;
    if (cur_key == k)
        return t->key;
    else if (k < cur_key)
        return kth_element(t->l, k);
    else
        return kth_element(t->r, k - cur_key);
}

pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}

void output (pitem t) {
    if (!t)  return;
    output (t->l);
    printf ("%d : %d\n", t->key, cnt(t));
    output (t->r);
}

void print_tree (pitem t, int ident=0) {
    if (!t) {
        cout << "\n";
        return;
    }
    print_tree(t->r, ident+4);
    if (ident) {
        cout << setw(ident) << " ";
    }
    cout << t->key << "\n";
    print_tree(t->l, ident+4);
}
