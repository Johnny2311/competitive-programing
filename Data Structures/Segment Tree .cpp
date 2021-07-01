/*Ejemplo de Algoritmos para implementar un Segment Tree + Lazy Propagation*/

const int MAXN = 2e5+5;
int a[MAXN];                                             
int s_tree[4 * MAXN];                                      
int lazy[4 * MAXN];                                       



void build(int cur,int l, int r){                    
	if (l == r){
	s_tree[cur] = a[l];  
    }
	else{
		int mid = l + r >> 1;                      
		build(cur<<1, l, mid);                          
		build(cur<<1 | 1, mid+1, r);                     
		s_tree[cur] = s_tree[cur<<1] + s_tree[cur<<1 | 1];       
	}                                                        
}


void update(int p, int v, int cur, int l, int r){
    if (l == r){
        s_tree[cur] = v;
    }
    else{
        int mid = l + r >> 1;
        if(p <= mid)
            update(p, v, cur<<1, l, mid);
        else
            update(p, v, cur<<1 | 1, mid+1, r);
        s_tree[cur] = s_tree[cur<<1] + s_tree[cur<<1 | 1];
    }
}


int query(int qL, int qR, int cur, int l, int r){
    if (r < qL || l > qR)
        return 0;
    if (l >= qL && r <= qR)
        return s_tree[cur];
    else{
        int mid = l + r >> 1;
        return query(qL, qR, cur<<1, l, mid) + query(qL, qR, cur<<1 | 1, mid+1, r);
    }

}

void push(int cur, int l, int r){
	if (lazy[cur] != 0){		                             
		s_tree[cur] += (r-l+1) * lazy[cur];		     
		if (l != r){                                  
			lazy[cur<<1] += lazy[cur];                      
			lazy[cur<<1 | 1] += lazy[cur];
		}
		lazy[cur] = 0;                                  
	}		
}
void update_lazy(int qL, int qR, int v, int cur, int l, int r){
	push(cur, l, r); 							 
    
	if (l > qR || r < qL)                          
    return;
    
	if (l >= qL && r <= qR){						 
		
		s_tree[cur] += (r-l+1) * v;				 
		 
		if (l != r){									 
			lazy[cur<<1] += v;							 
			lazy[cur<<1 | 1] += v;
		}
		return;
	}	
	int mid = l + r >> 1;                           
	update_lazy(qL, qR, v, cur<<1, l, mid);
	update_lazy(qL, qR, v, cur<<1 | 1, mid+1, r);
	s_tree[cur] = s_tree[cur<<1] + s_tree[cur<<1 | 1];           
}

int query_lazy(int qL, int qR, int cur, int l, int r){
	push(cur, l, r); 	
    
	if (l > qR || r < qL)
	return 0;
	
	if (l >= qL && r <= qR)                              
	return s_tree[cur];									      
	
	int mid = l + r >> 1;							  
    return query_lazy(qL, qR, cur<<1, l, mid) + query_lazy(qL, qR, cur<<1 | 1, mid+1, r);	
}



