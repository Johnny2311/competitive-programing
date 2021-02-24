 /*
 * Se construye una matriz M tal que M * A = B siendo A la matriz columna de los casos bases conocidos de la
 * recurrencia en orden decreciente (con respecto al indice) y B la matriz columna de los terminos a hallar.
 * Luego de formar la matriz A y hallar M se eleva esta ultima al exponente n - k (siendo k el indice de la
 * maxima posicion conocida de la recurrencia y n el indice a hallar); luego se multiplica el resultado
 * por A y la solucion al (n+1)th elemento de la recurrencia se encuentra en B[0][0]
 *
 *
 * EJEMPLOS:
 *
 * F(n) = F(n-1) + F(n-2)              //Fibonacci recurrence
 *
 *   M          A            B
 * [1 1]  *  [ F(n) ]  =  [F(n+1)]
 * [1 0]     [F(n-1)]     [ F(n) ]
 *
 *
 * F(n) = a*F(n-1) + b*F(n-2)          //Modified fibonacci recurrence (with constants)
 *
 *   M          A            B
 * [a b]  *  [ F(n) ]  =  [F(n+1)]
 * [1 0]     [F(n-1)]     [ F(n) ]
 *
 *
 * F(n) = a*F(n-1) + c*F(n-3)           //Missing one element, F(n-2)
 *
 *    M           A            B
 * [a 0 c]  *  [ F(n) ]  =  [F(n+1)]
 * [1 0 0]     [F(n-1)]     [ F(n) ]
 * [0 1 0]     [F(n-2)]     [F(n-1)]
 *
 *
 * F(n) = a*F(n-1) + b*G(n-2) + c       //Two recurrences + constants
 * G(n) = d*G(n-1) + e*G(n-2) + f
 *
 *      M              A            B
 * [a 1 0 b 0]  *  [ F(n) ]  =  [F(n+1)]
 * [0 1 0 0 0]     [  c   ]     [  c   ]
 * [0 0 d e 1]     [ G(n) ]     [G(n+1)]
 * [0 0 1 0 0]     [G(n-1)]     [ G(n) ]
 * [0 0 0 0 1]     [  f   ]     [G(n-1)]
 *
 *
 * ESPECIAL CASE:
 *
 * Si F(n) depende de la paridad de n
 * F(n) = a*F(n-1) + b*F(n-2)   n is even
 * F(n) = c*F(n-2) + d*F(n-3)   n is odd
 *
 * ANSWER:
 * Se crean dos matrices (Modd and Meven) y una matriz M = Modd * Meven,
 * luego la solucion es:
 * F(n) = M^(n/2) * A               n is odd
 * F(n) = Mobb * M^((n-1)/2) * A    n is even
 *
 * ALTERNATIVE ANSWER:
 * Se divide la recurrencia F(n) en dos recurrencias F(n) y G(n) de modo que
 * F(n) = a*G(n-1) + b*F(n-2)   n is even
 * G(n) = c*G(n-2) + d*F(n-3)   n is odd
 *
 * -Los casos bases son los mismos para ambas (F(n) = G(n))
 * -Para resolver F(n) se calcula la exponenciacion normalmente y la solucion sera (la posicion en B)
 * F(n) -> n is even
 * G(n) -> n is odd
 *
 *
 * ANOTHER APLICATIONS:
 * -Numero de caminos de longitud N entre dos vertices (unweighted directed graph):
 * Se toma la matriz de adyacencia del grafo (M) y se eleva a N, el numero de caminos entre los
 * vertices u-v sera M[u][v]
 *
 * -Camino mas corto entre dos vertices usando N aristas:
 * Se toma la matriz de adyacencia (esta vez con los costos) y se eleva a N, usando el producto distancia
 * al multiplicar (C[i][j] = min(A[i][k] + B[k][j]) para k=[1, N]), la solucion para u-v sera M[u][v]
 *
 *
 */

typedef long long ll;

const int K = 5, MOD = 1e9+7;

struct M{
    ll m[K][K];
};

M operator*(const M &a, const M &b){
    M res;
    int i, j, k;
    for (i=0; i<K; i++){
        for (j=0; j<K; j++){
            for (k=res.m[i][j]=0; k<K; k++){
                res.m[i][j] += (a.m[i][k]*b.m[k][j])%MOD;
                res.m[i][j] %= MOD;
            }
        }
    }
    return res;
}

M bpow(const M &b, ll e){
    if(e==1) return b;
    if(e&1) return b*bpow(b, e-1);
    M ans = bpow(b, e/2);
    return ans * ans;
}

