const int MAXN = 2e5+5;
const int LOG = 22;

int depth[MAXN], up[MAXN][LOG], weight[MAXN][LOG];
vvii tree;

void init() {
    memset(up, -1, sizeof up);
    memset(depth, -1, sizeof depth);
    memset(weight, 0, sizeof weight);
}

void dfs(int u, int p = -1, int d = 0){
    up[u][0] = p;
    depth[u] = d;

    for (int k = 1; k < LOG; ++k) {
        if (~up[u][k-1]) {
            up[u][k] = up[up[u][k-1]][k-1];
            weight[u][k] = weight[u][k-1] + weight[up[u][k-1]][k-1];
        }
    }

    for (ii e : tree[u]) {
        int v = e.fst, w = e.snd;
        if(v == p) continue;
        weight[v][0] = w;
        dfs(v, u, d + 1);
    }
}

int lca(int u, int v){
    if (depth[u] > depth[v]) swap(u, v);

    int k = LOG - 1;
    while (depth[v] > depth[u]) {
        if (~up[v][k] && depth[up[v][k]] >= depth[u]) {
            v = up[v][k];
        }
        k--;
    }

    if (u == v) return u;

    k = LOG - 1;
    while (~k) {
        if (~up[v][k] && ~up[u][k] && up[v][k] != up[u][k]) {
            v = up[v][k];
            u = up[u][k];
        }
        k--;
    }

    return up[v][0];
}

int weigth_path(int u, int v){          //sum of edge's weight of the path
    if (depth[u] > depth[v]) swap(u, v);

    int k = LOG - 1, w = 0;
    while (depth[v] > depth[u]) {
        if (~up[v][k] && depth[up[v][k]] >= depth[u]) {
            w += weight[v][k];
            v = up[v][k];
        }
        k--;
    }

    if (u == v) return w;

    k = LOG - 1;
    while (~k) {
        if (~up[v][k] && ~up[u][k] && up[v][k] != up[u][k]) {
            w += weight[v][k] + weight[u][k];
            v = up[v][k];
            u = up[u][k];
        }
        k--;
    }

    return weight[v][0] + weight[u][0] + w;
}

int crawl(int v, int kth) {         //kth anncestor of v (it has to exist)
    for (int i = 0; i < LOG; ++i) {
        if ((1<<i)&kth) {
            v = up[v][i];
        }
    }
    return v;
}

int len_path(int v, int u) {        //amount of nodes in path
    if (depth[u] > depth[v]) swap(u, v);
    int k = LOG - 1, d = 0;
    while (depth[v] > depth[u]) {
        if (~up[v][k] && depth[up[v][k]] >= depth[u]) {
            v = up[v][k];
            d += (1<<k);
        }
        k--;
    }
    return d;
}

int k_th(int v, int u, int kth){    //kth node from v to u
    int anc = lca(v, u);
    int len = len_path(v, anc);
    if (len >= kth)
        return crawl(v, kth);
    kth -= len;
    len = len_path(u, anc);
    return crawl(u, len - kth);
}
