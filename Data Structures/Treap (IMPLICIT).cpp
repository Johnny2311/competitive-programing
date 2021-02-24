typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    bool rev;           // for operation reverse(l, r)
    pitem l, r;
    item() {}
    item(int val) : value(val), prior(rand()), l(nullptr), r(nullptr) {}
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}


//left tree -> less than key
//right tree -> greater or equal than key
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = nullptr );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void insert (pitem & t, pitem it, int pos) {    //insert it in pos 
    pitem t1, t2;
    split(t, t1, t2, pos);
    merge(t1, t1, it);
    merge(t, t1, t2);
}

void push_back(pitem & t, pitem it) {
    merge(t, t, it);
}

void erase (pitem & t, int key, int add=0) {    //erase by implicit key = pos
    if (!t) return;
    int cur_key = add + cnt(t->l);
    if (key == cur_key)
        merge(t, t->l, t->r);
    else if (key < cur_key)
        erase (t->l, key, add);
    else
        erase (t->r, key, add + 1 + cnt(t->l));
    upd_cnt(t);
}

void reverse (pitem &t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void output (pitem t) {
    if (!t)  return;
    push (t);
    output (t->l);
    cerr << t->value << " ";
    output (t->r);
}
