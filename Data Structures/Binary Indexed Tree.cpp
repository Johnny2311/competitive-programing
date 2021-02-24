const int MAXN = 1e6+5, LOGN = 22;
int biTree[MAXN];
 
int sum(int k) {
    int s = 0;
    while (k >= 1) {
        s += biTree[k];
        k ^= k&-k;
    }
    return s;
}
 
void add(int k, int x) {
    while (k < MAXN) {
        biTree[k]+=x;
        k += k&-k;
    }
}

int bit_search(int v) {      //lower_bound(v) - Largest prefix sum less tham v 
	int sum = 0, pos = 0;
	for(int i=LOGN; i>=0; i--){
		if(pos + (1 << i) < MAXN && sum + biTree[pos + (1 << i)] < v){
			sum += biTree[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}
