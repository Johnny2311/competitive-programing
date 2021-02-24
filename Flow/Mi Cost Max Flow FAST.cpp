#include<bits/stdc++.h>

using namespace std;


const int MAXA = 5000;
const int MAXV = 100000;
const int INF = 1e9 + 7;

int e , u[MAXA], v[MAXA], w[MAXA], cap[MAXA], last[MAXV], next1[MAXA];
int pre[MAXV], d[MAXV];
bool inq[MAXV];
queue<int> q;
void addEdge(int a, int b, int co, int ca)
{
    u[e] = a;
    v[e] = b;
    w[e] = co;
    cap[e] = ca;
    next1[e] = last[a];
    last[a] = e++;
    u[e] = b;
    v[e] = a;
    w[e] = -co;
    cap[e] = 0;
    next1[e] = last[b];
    last[b] = e++;
}
void init()
{
    e = 0;
    memset(last, -1, sizeof(last));
}

bool spac(int s, int t, int cnt)
{
    int x,y, i;
    memset(pre, -1, sizeof(pre));
    memset(inq, 0, sizeof(inq));
    for(i = 0; i <= cnt; ++i) d[i] = INF;

    d[s] = 0;
    inq[s] = true;
    q.push(s);

    while(!q.empty())
    {
        x = q.front();
        q.pop();

        inq[x] = false;
        for(i = last[x]; i != -1; i = next1[i])
        {
            y = v[i];
            if(cap[i] != 0 && d[y] > d[x] + w[i])
            {
                d[y] = d[x] + w[i];
                pre[y] = i;
                if(!inq[y])
                {
                    inq[y] = true;
                    q.push(y);
                }
            }
        }
    }

    return d[t] != INF;
}
int cost, flow;

ii mfmc(int s, int t, int cnt)
{
    cost = flow = 0;
    int i, tmp;
    while(spac(s, t, cnt))
    {
        tmp = INF;
        for(i = pre[t]; i != -1; i = pre[u[i]])
            tmp = min(tmp, cap[i]);

        for(i = pre[t]; i != -1; i = pre[u[i]])
        {
            cap[i] -= tmp;
            cap[i^1] += tmp;

            cost += w[i];
        }
        flow += tmp;
    }
    return {flow,cost};
}