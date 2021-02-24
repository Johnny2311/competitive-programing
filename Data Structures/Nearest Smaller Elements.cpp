//Minimum to the left and to the right
//For maximum just multiply the whole array by -1 
// 0 - indexed

void preprocess(vi &arr, vi &left, vi &right){   
    stack<int> s;
    int n = sz(arr);
    for(int i=0; i<n; i++){
        while(!s.empty() && arr[s.top()] > arr[i])
            s.pop();
        if(s.empty())
            left[i] = -1;
        else
            left[i] = s.top();
        s.push(i);
    }

    while(!s.empty()) s.pop();

    for (int i=n-1; i>=0; i--){
        while(!s.empty() && arr[s.top()] >= arr[i])
            s.pop();
        if(s.empty())
            right[i] = n;
        else
            right[i] = s.top();
        s.push(i);
    }
}
