#define gc getchar
#define pc putchar
//to speed up loops
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

template <class num>inline void read(num &x){
    char c;
    while(isspace(c=gc()));
    bool neg=false;
    if(!isdigit(c)) neg=(c=='-'), x=0;
    else x = c-'0';
    while(isdigit(c=gc())) x=(x<<3)+(x<<1)+c-'0';
    if(neg) x=-x;

}


template<class num>inline void write(const num &x, const char c='\n'){
    static char a[20];
    register int i=0;
    num n=x;
    if(n<0){pc('-'); n=-n;}
    if(n==0){pc('0'); pc(c); return;}
    while(n){
        a[i++] = (n%10)+'0';
        n/=10;
    }
    for (i=i-1; i>=0; i--)
        pc(a[i]);
    pc(c);
}