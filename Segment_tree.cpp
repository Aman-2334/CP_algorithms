#include <bits/stdc++.h>
using namespace std;

class SegmentTree{
    vector<long long> tree, lazyTree;
    int sz;
    
    long long minSegmentTree(vector<int>& nums,int i, int l, int r){
        if(l == r) return tree[i] = nums[l];
        tree[i] = min(minSegmentTree(nums,2*i+1,l,(l+r)/2),
                        minSegmentTree(nums,2*i+2,(l+r)/2+1,r));
        return tree[i];
    }
    
    long long maxSegmentTree(vector<int>& nums,int i, int l, int r){
        if(l == r) return tree[i] = nums[l];
        tree[i] = max(maxSegmentTree(nums,2*i+1,l,(l+r)/2),
                        maxSegmentTree(nums,2*i+2,(l+r)/2+1,r));
        return tree[i];
    }
    
    long long sumSegmentTree(vector<int>& nums,int i, int l, int r){
        if(l == r) return tree[i] = nums[l];
        tree[i] = sumSegmentTree(nums,2*i+1,l,(l+r)/2)+
                        sumSegmentTree(nums,2*i+2,(l+r)/2+1,r);
        return tree[i];
    }
    
    long long getMin(int l, int r, int l1, int r1, int i){
        lazyPropogation(i,l1,r1);
        if(r1 < l || l1 > r) return LONG_MAX;
        if(r1 <= r && l1 >= l) return tree[i];
        return min(getMin(l,r,l1,((l1+r1))/2,2*i+1),getMin(l,r,((l1+r1))/2+1,r1,2*i+2));
    }
    
    long long getMax(int l, int r, int l1, int r1, int i){
        lazyPropogation(i,l1,r1);
        if(r1 < l || l1 > r) return LONG_MIN;
        if(r1 <= r && l1 >= l) return tree[i];
        
        return max(getMax(l,r,l1,(l1+r1)/2,2*i+1),getMax(l,r,(l1+r1)/2+1,r1,2*i+2));
    }
    
    long long getSum(int l, int r, int l1, int r1, int i){
        lazyPropogation(i,l1,r1);
        if(r1 < l || l1 > r) return 0;
        if(r1 <= r && l1 >= l) return tree[i];
        
        return getSum(l,r,l1,(l1+r1)/2,2*i+1)+getSum(l,r,(l1+r1)/2+1,r1,2*i+2);
    }
    
    long long pointUpdate(int n, int k, int l1, int r1, int i){
        lazyPropogation(i,l1,r1);
        if(l1 == r1 && r1 == k) return tree[i] = n;
        if(k <= ((l1+r1))/2)
            return tree[i] = min(pointUpdate(n,k,l1,(l1+r1)/2,2*i+1),tree[2*i+2]);

        return tree[i] = min(tree[2*i+1],pointUpdate(n,k,(l1+r1)/2+1,r1,2*i+2));
    }
    
    long long rangeUpdate(int n, int l, int r, int l1, int r1, int i){
        lazyPropogation(i,l1,r1);
        if(r1 < l || l1 > r) return tree[i];
        if(r1 <= r && l1 >= l){
            tree[i] += n*(r1-l1+1);
            if(r1 != l1){
                lazyTree[2*i+1] += n; 
                lazyTree[2*i+2] += n;
            }
            return tree[i];
        }
        
        return tree[i] = rangeUpdate(n,l,r,l1,(l1+r1)/2,2*i+1)+rangeUpdate(n,l,r,(l1+r1)/2+1,r1,2*i+2);
    }
    
    void lazyPropogation(int i, int l, int r){
        if(lazyTree[i] != 0){
            tree[i] += lazyTree[i]*(r-l+1);
            if(r != l){
                lazyTree[2*i+1] += lazyTree[i]; 
                lazyTree[2*i+2] += lazyTree[i];
            }
            lazyTree[i] = 0;
        }
    }

    public:
    SegmentTree(vector<int>& nums) : sz(nums.size()), tree(4*nums.size()), lazyTree(4*nums.size()){
        minSegmentTree(nums,0,0,sz-1);
        // for(int v : tree) cout<<v<<",";
        // cout<<endl;
        // maxSegmentTree(nums,0,0,nums.size()-1);
        // sumSegmentTree(nums,0,0,nums.size()-1);
    }
    
    long long getMin(int l, int r){
        return getMin(l,r,0,sz-1,0);
    }
    
    long long getMax(int l, int r){
        return getMax(l,r,0,sz-1,0);
    }
    
    long long getSum(int l, int r){
        return getSum(l,r,0,sz-1,0);
    }
    
    long long pointUpdate(int n, int k){
        return pointUpdate(n,k,0,sz-1,0);
    }
    
    long long rangeUpdate(int n, int l, int r){
        return rangeUpdate(n,l,r,0,sz-1,0);
    }
    
    void printTree(){
        for(int v : tree) cout<<v<<",";
        cout<<endl;
    }
};
