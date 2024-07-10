class FenwickTree{
    vector<int> tree;
    int sz;

    public:
    FenwickTree(vector<int>& nums) : tree(nums.size()+1,0), sz(nums.size()){
        for(int i=1; i<=sz; ++i){
            update(i,nums[i-1]);
        }
    }

    int query(int i){
        int s = 0;
        for(int j=i; j>0; j -= -j&j) s += tree[j];
        return s;
    }

    void update(int i, int k){
        for(int j=i; j<=sz; j += -j&j){
            tree[j] += k;
        }
    }

    void printTree(){
        cout<<"FT: ";
        for(int i : tree) cout<<i<<",";
        cout<<endl;
    }
};
