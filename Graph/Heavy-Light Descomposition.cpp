/* Programa para saber cual es la arista de menor peso y cual la de mayor
en varios caminos de un arbol dado*/

#include <bits/stdc++.h>
#define pb push_back
#define INF (ii(INT_MAX, INT_MIN))
#define pc putchar_unlocked
#define gc getchar_unlocked
using namespace std;
typedef pair<int, int> ii;



const int MAXN = 1e5+5;
vector <ii> tree[MAXN];
int chain_heads[MAXN];
int DP[MAXN][25];
int LOG;

struct treeNode{
	int par, depth, size, pos_ST, chain;
} node[MAXN];

struct Edge{
	int weight, deeper_end;
} edge[MAXN];

struct segmentTree{
	int array[MAXN];
	ii tree[4*MAXN];
} s;

inline ii best(const ii &a, const ii &b){
	return ii(min(a.first, b.first), max(a.second, b.second));
}

void addEdge(int e, int u, int v, int w){
	tree[u].pb(ii(v, e));
	tree[v].pb(ii(u, e));
	
	edge[e].weight = w; 
}

void dfs(int curr, int prev, int dep){
	
	node[curr].par = prev;
	DP[curr][0] = prev;
	node[curr].depth = dep;
	node[curr].size = 1;
	
	for (int i=0; i<tree[curr].size(); i++){
		int v = tree[curr][i].first, e = tree[curr][i].second;
		
		if(v == prev) continue;
		
		edge[e].deeper_end = v;   //Solo para Update
		
		dfs(v, curr, dep+1);
		
		node[curr].size += node[v].size;
	}
}

void HLD(int curr_node, int id, int &edge_counted, int &curr_chain){
	
	if(chain_heads[curr_chain] == -1) 
		chain_heads[curr_chain] = curr_node;
		
	node[curr_node].chain = curr_chain;
	
	node[curr_node].pos_ST = edge_counted;
	
	s.array[edge_counted++] = edge[id].weight;
	
	int spc = -1, ed_id;
	for (int i=0; i<tree[curr_node].size(); i++){
		int v = tree[curr_node][i].first, e = tree[curr_node][i].second;
		
		if (v == node[curr_node].par) continue;
		
		if (spc == -1 || node[spc].size < node[v].size){
			spc = v;
			ed_id = e;
		}
	}
	
	if (spc != -1)
		HLD(spc, ed_id, edge_counted, curr_chain);
		
	for (int i=0; i<tree[curr_node].size(); i++){
		int v = tree[curr_node][i].first, e = tree[curr_node][i].second;
		
		if(v == spc || v == node[curr_node].par) continue;
		curr_chain++;
		HLD(v, e, edge_counted, curr_chain);
	}
}

int LCA(int u, int v){
	
	if(node[u].depth > node[v].depth) swap(u, v);
	
	int j=LOG;
	
	while(node[v].depth > node[u].depth){
		if(DP[v][j] != -1 && node[DP[v][j]].depth >= node[u].depth){
			v = DP[v][j];
		}
		j--;
	}
	
	if(u==v) return u;
	
	
	j=LOG;
	
	while(j>=0){
		if(DP[v][j] != -1 && DP[u][j] != -1 && DP[v][j] != DP[u][j]){
			v = DP[v][j];
			u = DP[u][j];
		}
		j--;
	}
	return DP[u][0];
}

void build_ST(int node, int l, int r){
	if(l==r){
		s.tree[node] = ii(s.array[l], s.array[l]);
	}else{
		int mid = (l+r)/2;
		build_ST(2*node, l, mid);
		build_ST(2*node+1, mid+1, r);
		s.tree[node] = best(s.tree[2*node], s.tree[2*node+1]);
	}
}

ii query_ST(int node, int l, int r, int limInf, int  limSup){
	if(l>limSup || r<limInf) 
		return INF;
	
	if(l>=limInf && r<=limSup)
		return s.tree[node];
	
	int mid = (l+r)/2;
	ii child_1 = query_ST(2*node, l, mid, limInf, limSup);
	ii child_2 = query_ST(2*node+1, mid+1, r, limInf, limSup);
	return best(child_1, child_2);
}

ii RMQ(int u, int v, int n){
	return query_ST(1, 1, n-1, u, v);
}

ii crawl_tree(int u, int v, int n){
	
	int chain_u, chain_v = node[v].chain;
	ii ans = INF;
	
	while(true){
		chain_u = node[u].chain;
		
		if(chain_u == chain_v){
			if(u==v);
			else{
				ans = best(ans, RMQ(node[v].pos_ST+1, node[u].pos_ST, n));
			}
			break;
		}
		
		else{
			ans = best(ans, RMQ(node[chain_heads[chain_u]].pos_ST, node[u].pos_ST, n));
			
			u = node[chain_heads[chain_u]].par;
		}
	}
	
	return ans;
}

ii min_max_Edge(int u, int v, int n){
	
	int lca = LCA(u, v);
	ii ans = best(crawl_tree(u, lca, n), crawl_tree(v, lca, n));
	
	return ans;
}
 

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout .tie(0);
	
	int N;
	cin >> N;
	
	int u, v, w;
	for (int i=0; i<N-1; i++){
		cin >> u >> v >> w
		addEdge(i, u, v, w);
	}
	
	memset(chain_heads, -1, sizeof chain_heads);
	memset(DP, -1, sizeof DP);
	
	int edge_counted=0, curr_chain=0;
	
	dfs(1, -1, 0);
	
	
	HLD(1, N-1, edge_counted, curr_chain);
	
	build_ST(1, 1, N-1);
	

	LOG = log2(N);	
	
	for (int j=1; j<=LOG; j++){
		for (int i=1; i<=N; i++){
			DP[i][j] = DP[DP[i][j-1]][j-1];
		}
	}	

	int Q, a, b;
	cin >> Q;
	while(Q--){
		cin >> a >> b;
		ii ans = min_max_Edge(a, b, N);
		cout << ans.first << " ";
		cout << ans.second << "\n";
	}	
	
	return 0;
}

