
string T;//cadena donde buscar(where)
string P;//cadena a buscar(what)
int b[MAXLEN];//back table b[i] maximo borde de [0..i)
void kmppre(){
    int i =0, j=-1; b[0]=-1;
    while(i<sz(P)){
        while(j>=0 && P[i] != P[j]) j=b[j];
        i++, j++, b[i] = j;
    }
}

void kmp(){
    int i=0, j=0;
    while(i<sz(T)){
        while(j>=0 && T[i]!=P[j]) j=b[j];
        i++, j++;
        if(j==sz(P)) printf("P is found at index %d in T\n", i-j), j=b[j];
    }
}

int autom[MAXN][26]; //Para optimizar las transciciones O(n*26)
void buildAut(){
    for(int i=0; i<MAXN; i++){
        for (int j=0; j<26; j++){
            char c = 'a' + j;
            if(i>=0 && c != P[i])
                autom[i][j] = autom[b[i]][j];
            else
                autom[i][j] = i+1;
            
        }
    }
}

