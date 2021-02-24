const int MAXN = 5e5+5;

int dp[MAXN];

struct state {
    int len, link, first_pos;
    bool isClone;
    map<char, int> next;
};

state st[MAXN * 2];
int sz, last;

void sa_init(){
    for (int i=0; i<sz; i++) st[i].next.clear();
    st[0].len = 0;
    st[0].link = -1;
    sz = last=0;
    ++sz;
}

void sa_extend(char c){
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = st[cur].len - 1;
    st[cur].isClone = false;
    int p = last;
    while(p != -1 && !st[p].next.count(c)){
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p == -1){
        st[cur].link = 0;
    }else{
        int q = st[p].next[c];
        if(st[p].len + 1 == st[q].len){
            st[cur].link = q;
        }else{
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;
            st[clone].isClone = true;
            while(p != -1 && st[p].next[c] == q){
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

int f(int u){       //Amount of distinct substrings (f(n) - 1)
    if(u==last) return 1;
    if(~dp[u]) return dp[u];

    int ans = 1;
    for (auto v : st[u].next){
        ans += f(v.second);
    }
    return dp[u] = ans;
}
                                //sa over str + str
int rot(int u, int sz=0){       //Minimun number of rotation to make str become the smallest lexicographical order string
    while(sz < sz(s)/2){
        u = st[u].next.begin()->second;
        sz++;
    }
    return st[u].firstpos - sz + 1;
}

string lcs(string &t){
    int v=0, l=0, best=0, bestpos=0;
    for (int i=0; i<sz(t); i++){
        while(v && !st[v].next.count(t[i])){
            v = st[v].link;
            l = st[v].len;
        }
        if(st[v].next.count(t[i])){
            v = st[v].next[t[i]];
            l++;
        }
        if(l > best){
            best = l;
            bestpos = i;
        }
    }
    return  t.substr(bestpos-best+1, best);
}