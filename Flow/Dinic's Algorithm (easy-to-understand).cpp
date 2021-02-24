struct Dinic {
    struct Edge {
        int u, v;
        ll cap, flow = 0;
        Edge(int u, int v, ll cap) : u(u), v(v), cap(cap) {}
    };

    vector<Edge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edges.push_back(Edge(u, v, cap));
        edges.push_back(Edge(v, u, 0));
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }

    bool bfs(int s, int t) {
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                if (level[edges[id].v] != -1 || edges[id].cap - edges[id].flow < 1)
                    continue;
                level[edges[id].v] = level[u] + 1;
                q.push(edges[id].v);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int s, int t, ll pushed) {
        if (pushed == 0)
            return 0;
        if (s == t)
            return pushed;
        for (int& cid = ptr[s]; cid < (int)adj[s].size(); cid++) {
            int id = adj[s][cid];
            int v = edges[id].v;
            if (level[s] + 1 != level[v] || edges[id].cap - edges[id].flow < 1)
                continue;
            ll tr = dfs(v, t, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll max_flow(int s, int t, ll flow=oo) {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            if (!bfs(s, t))
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, flow)) {
                f += pushed;
            }
        }
        return f;
    }
};
