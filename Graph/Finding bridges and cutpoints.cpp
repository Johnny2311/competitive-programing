 
vvi adj; // adjacency list of graph

vi tin, low, vis;   //low[u] stores the lowest tin[v] reachable from spanning subtree of u in DFS tree
                    //this tell us if there is a backedge from some descendent of u
int timer;

void dfs(int u, int p = -1) {
    vis[u] = 1;
    tin[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
                IS_BRIDGE(u, v);
            if (low[v] >= tin[u] && p != -1)
                IS_CUTPOINT(u);     //can be called multiple times for the same node
            ++children;
        }
    }
    if (p == -1 && children > 1)
        IS_CUTPOINT(u);
}

void find_bridges_and_cutpoints(int n) {  // number of nodes
    timer = 0;
    vis.assign(n, 0);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            dfs(i);
    }
} 
