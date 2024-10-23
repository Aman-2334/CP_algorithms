class FenwickTree{
    vector<int> bit;
    int n;

    FenwickTree(vector<int> const &a) : n(a.size()){
        bit.assign(n,0);
        for(int i=0; i<n; ++i){
            add(i,a[i]);
        }
    }

    int sum(int r){
        int res = 0;
        for(;r >= 0; r = (r & (r+1))-1) res = res + bit[r];
        return res;
    }

    int sum(int l, int r){
        return sum(r)-sum(l-1);
    }

    void add(int i, int d){
        for(; i<n; i = i | (i+1)) bit[i] = bit[i]+d;
    }
};
