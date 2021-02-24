#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

const int MAXN = 305;
int N, M;
int mat[MAXN][MAXN];
int height[MAXN];


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i=1; i<=N; i++){
        for (int j=1; j<=M; j++){
            cin >> mat[i][j];
        }
    }

    int sol=0;

    for (int i=1; i<=N; i++){
        for (int j=1; j<=M; j++){
            if(mat[i][j] > 0) height[j] = 0;
            else height[j]++;
        }

        stack <ii> stk;
        
        for (int j=1; j<=M; j++){
            int cur_width = 0;

            while(!stk.empty() && height[j] <= stk.top().first){
                int h = stk.top().first, w = stk.top().second;
                cur_width += w;

                sol = max(sol, 2*(h + cur_width));
                stk.pop();
            }

            if(height[j]) stk.push({height[j], cur_width + 1});
        }
        
        int t_width=0;
        while(!stk.empty()){
            int h = stk.top().first, w = stk.top().second;
            t_width += w;

            sol = max(sol, 2*(h + t_width));
            stk.pop();
        }
    }

    cout <<  sol << "\n";

    return 0;
}

/*
4 5
5 0 3 1 1
0 0 0 9 1
0 0 0 1 0
3 2 9 1 0

4 5
5 0 3 1 1
1 1 0 9 1
0 3 1 1 0
3 2 9 1 1

4 5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1

2 5
0 1 1 1 1
0 0 1 9 1

4 5
0 1 1 1 1
0 0 1 9 1
0 0 0 1 0
3 2 9 1 0

4 6
1 1 0 1 1 1
1 0 0 0 1 1
0 0 0 0 0 1
3 2 9 1 1 1
*/





