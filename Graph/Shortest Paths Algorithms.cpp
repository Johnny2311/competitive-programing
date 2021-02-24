#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define gc getchar
#define pc putchar
#define pb push_back
#define eb emplace_back
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector <int> vi;

int N;
bool taken[1005][1005];
int movx[] = {1, -1, 0, 0};
int movy[] = {0, 0, -1, 1};

const int MAXN = 1e5+5;
vector<ii> adj[MAXN];
int distAll[1005][1005], MatAdy[1005][1005];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb(ii(v, w));
        adj[v].pb(ii(u, w));
        MatAdy[u][v] = MatAdy[v][u] = w;
    }



    vi dist(n+1, INF);
    dist[1] = 0;

    //Bellman-Ford
    for (int k=0; k<n-1; k++){
        for (int i=1; i<=n; i++){
            for (int j=0; j<adj[i].size(); j++){
                int v = adj[i][j].first, w = adj[i][j].second;
                if(dist[v] > dist[i] + w)
                    dist[v] = dist[i] + w;
            }
        }
    }
    

    //Dijkstra
    priority_queue<ii> pq;
    pq.push({0, 1});
    
    vi dist(n+1, INF);
    dist[1] = 0;
    
    while(!pq.empty()){
        int u = pq.top().second, d = -pq.top().first;
        pq.pop();

        if(dist[u] < d) continue;

        for (int i=0; i<adj[u].size(); i++){
            int v = adj[u][i].first, w = adj[u][i].second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }
   

    //Floyd-Warshall
    for (int i=1; i<=n; i++)  distAll[i][i] = 0;
    for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) if(i!=j) distAll[i][j] = INF;
    for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) if(MatAdy[i][j]) distAll[i][j] = MatAdy[i][j];

    for (int k=1; k<=n; k++){
        for (int i=1; i<=n; i++){
            for (int j=1; j<=n; j++){
                if(distAll[i][j] > distAll[i][k] + distAll[k][j])
                    distAll[i][j] = distAll[i][k] + distAll[k][j];

            }
        }
    }


//    for (int i=1; i<=n; i++) cout << i << ": " <<  dist[i] << "\n";

    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cout << distAll[i][j] << " ";
        }
        cout << "\n";
    }


}


/*
5 7
 1 2 2
 1 3 3
 1 4 7
 3 4 2
 2 4 3
 2 5 5
 4 5 2

 5 6
 1 2 5
 1 5 1
 1 4 9
 5 4 2
 4 3 7
 2 3 2

 */




