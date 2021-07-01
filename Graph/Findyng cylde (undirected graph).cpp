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
typedef vector<ii> vii;
typedef vector<vii> vvii;

const int MAXN = 1e5+5;


vi graph[MAXN];
int n, m;


int edge=0, node=0;
bool visNode[MAXN];
bool dfs(int u){        //HandShaking's Theorem, count the number of nodes and edges
    node++;
    visNode[u] = 1;
    for (int i=0; i<graph[u].size(); i++){
        int v = graph[u][i];
        edge++;
        if(!visNode[v]){
            dfs(v);
        }
    }
}

bool dfs(int u, int p){         //Cycle is founded if there is a node that is visited and isn't my father
    visNode[u] = 1;
    
    for (int i=0; i<graph[u].size(); i++){
        int v = graph[u][i];
        if(!visNode[v]){
            if (dfs(v, u))
                return true;
        }else if(v != p) return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    for (int i=1; i<=n; i++){
        if(!visNode[i]){
            dfs(i);
            edge /= 2;
            if(node - 1 == edge) cout << "There is no cycle\n";
            else cout << "There is a cycle\n";
            node=0;
            edge=0;
        }
    }


    return 0;
}

/*
6 5
 1 2
 2 3
 4 5
 4 6
 5 6

 */
