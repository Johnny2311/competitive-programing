typedef complex<ll> P;
#define X real()
#define Y imag()
#define dist(x) abs(x)  //for complex numbers only

// sum x[i] * y[i+1] - x[i+1] * y[i] from i=[1,n] (circular fashion)
//cross product

P point[MAXN];
double area=0;
for (int i=0; i<n; i++){
    area += point[i].X * point[(i+1)%n].Y - point[(i+1)%n].X * point[i].Y;
}