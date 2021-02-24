 
int parent[MAXN], rnk[MAXN];

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}

struct Edge {
    int u, v, w;
    bool operator<(Edge const& other) {
        return w < other.w;
    }
};


//inside main
int n;
vector<Edge> edges;

for (int i = 0; i < n; i++)
    make_set(i);

sort(edges.begin(), edges.end());

int cost = 0;
for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.w;
        union_sets(e.u, e.v);
    }
}
