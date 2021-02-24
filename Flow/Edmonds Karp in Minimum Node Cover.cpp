/*
 * Aplicacion del algoritmo de Edmonds Karp (flujo maximo) para Minimum Node Cover
 * que es equivalente a el Maximum Matching
 */

#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;

const int MAXN = 205;
const int oo = 1e9;
vi adj[MAXN];
int capacity[MAXN][MAXN];

int bfs(int s, int t, vi &parent){
    fill(all(parent), -1);
    parent[s] = -2;
    queue<ii> q;
    q.push({s, oo});

    while(!q.empty()){
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]){
            if(parent[next] == -1 && capacity[cur][next]){
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if(next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }

    }
    return 0;
}


int max_flow(int s, int t){
    int flow=0;
    vi parent(MAXN);
    int new_flow;

    while(new_flow = bfs(s, t, parent)){
        flow += new_flow;
        int cur = t;
        while(cur != s){
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

void add_edge(int src, int dst, int cap){
    adj[src].pb(dst);
    adj[dst].pb(src);
    capacity[src][dst] = cap;
}

void clear(){
    for (auto &v : adj) v.clear();
    memset(capacity, 0, sizeof capacity);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    for(int k=1; k<=t; k++){
        int n, m;
        cin >> n;
        vi a(n);
        for (int &v : a) cin >> v;
        cin >> m;
        vi b(m);
        for (int &v : b) cin >> v;

        for (int i=0; i<n; i++){
            adj[0].pb(i+1);
//            adj[i+1].pb(0);
            capacity[0][i+1] = 1;
        }

        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                if(b[j]%a[i]==0){
                    adj[i+1].pb(n+1+j);
                    adj[n+1+j].pb(i+1);
                    capacity[i+1][n+1+j] = 1;
                }
            }
        }

        for (int j=0; j<m; j++){
            adj[n+1+j].pb(n+m+1);
//            adj[n+1+m].pb(n+j+1);
            capacity[n+1+j][n+m+1] = 1;
        }


        cout << "Case " << k  << ": "<< max_flow(0, n+m+1) << "\n";
        clear();

    }


    return 0;
}

/*
2
4 2 3 4 5
4 6 7 8 9
3
100 200 300
1
150
 */