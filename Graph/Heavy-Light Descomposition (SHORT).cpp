const int MAXN = 2e5+5;
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int cur_pos;

int dfs(int u) {
    int size = 1;
    int max_sz = 0;
    for (int v : tree[u]) {
        if (v == parent[u]) continue;
        parent[v] = u, depth[v] = depth[u] + 1;
        int v_sz = dfs(v);
        size += v_sz;
        if (v_sz > max_sz)
            max_sz = v_sz, heavy[u] = v;
        
    }
    return size;
}

int decompose(int u, int h) {
    head[u] = h, pos[u] = ++cur_pos;
    if (~heavy[u])
        decompose(heavy[u], h);
    for (int v : tree[u]) {
        if (v != parent[u] && v != heavy[u])
            decompose(v, v);
    }
}

void init(){
    memset(heavy, -1, sizeof heavy);
    //define fst_node
    dfs(fst_node);
    descompose(fst_node, fst_node);
}

//define segment tree 
//LCA implicit
int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}