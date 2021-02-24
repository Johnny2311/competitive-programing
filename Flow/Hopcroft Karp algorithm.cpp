/*  Ejemplo de uso del Hopcroft Karp:
 *  Contar la cantidad de caballos que se pueden poner en un tablero con casillas inutilizadas
 *  sin que se ataquen entre si(Maximun Independent Set) 
 * 
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

namespace hk{
    const int MAXN=40005;
    const int NIL=0;
    const int oo=(1<<28);
    vector< int > graph[MAXN];
    int n=0, m, matching[MAXN], distance[MAXN];
    // n: number of nodes on left side, nodes are numbered 1 to n
    // m: number of nodes on right side, nodes are numbered n+1 to n+m

    void init(int _n){
        n = _n;
        for(int i=0;i<MAXN;i++)graph[i].clear();
        memset(matching, 0, sizeof matching);
        memset(distance, 0, sizeof distance);
    }
    bool bfs() {
        queue<int> q;
        for(int i=1; i<=n; i++)
            if(matching[i]==NIL) {
                distance[i] = 0;
                q.push(i);
            }
            else
                distance[i] = oo;

        distance[NIL] = oo;

        while(!q.empty()) {
            int left = q.front(); q.pop();
            if(left!=NIL) {
                for(int right : graph[left]) {
                    if(distance[matching[right]] == oo) {
                        distance[matching[right]] = distance[left] + 1;
                        q.push(matching[right]);
                    }
                }
            }
        }
        return (distance[NIL]!=oo);
    }
    bool dfs(int left) {
        if(left != NIL) {
            for(int right : graph[left]) {
                if(distance[matching[right]]==distance[left]+1)
                    if(dfs(matching[right])) {
                        matching[right] = left;
                        matching[left] = right;
                        return true;
                    }
            }
            distance[left] = oo;
            return false;
        }
        return true;
    }
    int hopcroft_karp() {
        int num_matching = 0;
        // matching[] is assumed NIL for all vertex in graph
        while(bfs())
            for(int i=1; i<=n; i++)
                if(matching[i]==NIL && dfs(i))
                    num_matching++;
        return num_matching;
    }
    void add(int a,int b){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

using namespace hk;

int mx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int my[] = {2, -2, 1, -1, 2, -2, 1, -1};

int M, N, K;

bool broken[205][205];
int pos[205][205];

bool ok(int x, int y){
    return x >= 1 && x <= M && y >= 1 && y <= N && !broken[x][y];
}

void clear(){
    memset(pos, 0, sizeof pos);
    memset(broken, 0, sizeof broken);
}

bool color(int x, int y){
    if(x&1){
        if(y&1) return 1;
        return 0;
    }else{
        if(y&1) return 0;
        return 1;
    }
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    for(int p=1; p<=t; p++){


        cin >> M >> N >> K;
        for (int i=0; i<K; i++){
            int x, y;
            cin >> x >> y;
            broken[x][y]=1;
        }


        int z=0;
        for (int i=1; i<=M; i++){
            for (int j=1; j<=N; j++){
                if(color(i, j) && !broken[i][j]) pos[i][j] = ++z;
            }
        }


        for (int i=1; i<=M; i++){
            for (int j=1; j<=N; j++){
                if(!color(i, j) && !broken[i][j]) pos[i][j] = ++z;
            }
        }





        init(z);
        for (int i=1; i<=M; i++){
            for (int j=1; j<=N; j++){
                if(pos[i][j] <= n && !broken[i][j]){
                    for (int k=0; k<8; k++){
                        int nx = i + mx[k];
                        int ny = j + my[k];
                        if(ok(nx, ny)){
                            add(pos[i][j], pos[nx][ny]);
                        }
                    }
                }
            }
        }



        cout << "Case " << p << ": " << M*N - K - hopcroft_karp() << "\n";

        clear();

    }


    return 0;
}

/*
2
8 8 0

2 5 4
 1 3
 1 4
 2 3
 2 4
 */
