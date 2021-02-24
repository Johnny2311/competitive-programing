typedef struct item * pitem;
struct item {
    int key, prior, cnt, occ;
    pitem l, r;
    item() { }
    item (int key) : key(key), prior(rand()), occ(1), l(nullptr), r(nullptr) { }
};

int cnt (pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
    if (t)
        t->cnt = t->occ + cnt(t->l) + cnt(t->r);
}

void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = nullptr;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
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

bool increment (pitem t, int key) {
    if (!t) return false;
    bool f;
    if (key == t->key)
        t->occ++, f = true;
    else
        f = increment((key < t->key ? t->l : t->r), key);
    upd_cnt(t);
    return f;
}

void insert (pitem & t, pitem it) {
    pitem t1, t2;
    split(t, it->key, t1, t2);
    if (!increment(t1, it->key))
        merge(t1, t1, it);
    merge(t, t1, t2);
}

int kth_element (pitem t, int k) {
    if (cnt(t->l) < k) {
        if (k <= cnt(t->l) + t->occ)
            return t->key;
        return kth_element(t->r, k - (t->occ + cnt(t->l)));
    }
    return kth_element(t->l, k);
}

void erase (pitem & t, int key) {
    if (!t) return;
    if (t->key == key)
        if (t->occ == 1)
            merge (t, t->l, t->r);
        else
            t->occ--;
    else
        erase (key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}
