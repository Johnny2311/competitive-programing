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
vi tree[MAXN], toLeaf, maxPath;

void f(int u, int p){

    for(int i=0; i<tree[u].size(); i++){
        int v = tree[u][i];
        if(v==p) continue;
        f(v, u);
        toLeaf[u] = max(toLeaf[u], toLeaf[v] + 1);
    }
}

int farNode, maxDist = INT_MIN;


void solve(int u, int p){
    int mx1=0, mx2=0;

    for(int i=0; i<tree[u].size(); i++){
        int v = tree[u][i];
        if(v==p) continue;
        if(toLeaf[v] > mx1){
            mx1 = toLeaf[v];
            mx2 = mx1;
        }else if(toLeaf[v] > mx2){
            mx2 = toLeaf[v];
        }
    }
    maxDist = max(maxDist, mx1 + mx2);
}



void dfs(int u, int p, int dist=0){
    if (dist > maxDist){
        maxDist = dist;
        farNode = u;
    }
    for (int v : tree[u]) {
        if(v == p) continue;
        dfs(v, u, dist+1);
    }
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    toLeaf.resize(N+1, 0);
    maxPath.resize(N+1, 0);

    for (int i=0; i<N-1; i++){
        int u, v;
        cin >> u >> v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
//     dfs(1, 0);
//    cout << "Farest node: " << farNode << "\nDistance: " << maxDist << "\n";
//    dfs(farNode, 0);
//    cout << "Diameter: " << maxDist << "\n";

    f(1, 0);
    solve(1, 0);
    cout << "Diameter: " << maxDist << "\n";

}


