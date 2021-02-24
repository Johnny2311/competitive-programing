const int MAXN=1e6+5;
const int K=26;

int index(char c){
    return c-'a';
}
int nxt[MAXN][K], cur_node;
int fail[MAXN], finish[MAXN], out[MAXN], cnt[MAXN];

void init(){
    cur_node=0;
    memset(nxt, 0, sizeof nxt);
    memset(fail, 0, sizeof fail);
    memset(finish, -1, sizeof finish);
    memset(out, 0, sizeof out);
    memset(cnt, 0, sizeof cnt);
    }

void insert (string &s, int id) {
    int u = 0;
    for (int i = 0; i < s.size(); ++i) {
        int c = index(s[i]);
        if (!nxt[u][c]) {
            nxt[u][c] = ++cur_node;
        }
        u = nxt[u][c];
    }
    finish[u] = id;
    ++cnt[u];
}
void buildf () {
    queue<int> q;
    for (int i = 0; i < K; ++i)
        if(nxt[0][i]) q.push(nxt[0][i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int link = fail[u];
        if(~finish[link])
            out[u] = link;
        else
            out[u] = out[link];
        for (int i = 0; i < K; ++i) {
            int v = nxt[u][i];
            if (v) {
                fail[v] = nxt[ fail[u] ][i];
                cnt[v] += cnt[ fail[v] ];
                q.push(v);
            }else{
                nxt[u][i] = nxt[ fail[u] ][i];
            }
        }
    }
}
int match (string &s) {
    int cur = 0, matches = 0;
    for (int i = 0; i < s.size(); ++i) {
        int c = index(s[i]);
        cur = nxt[cur][c];
        matches += cnt[cur];
        int t = cur;
        while (t != 0) {
            if (~finish[t])
                printf("founded string %d at index %d\n", finish[t], i-finish[i]+1);
            t = out[t];
        }
    }
    return matches;
}
