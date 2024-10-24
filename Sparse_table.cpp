#include <bits/stdc++.h>
using namespace std;

class SparseTable{
    vector<vector<int>> sparseTable;
    vector<int> logTable;

    void create_sparseTable(vector<int>& nums){
        int n = nums.size(), m = logTable[n]+1;
        sparseTable.assign(n,vector<int>(m));
        for(int j=0; j<m; ++j){
            for(int i=0; i+(1<<j)-1 < n; ++i){
                if(j == 0) sparseTable[i][j] = nums[i];
                else sparseTable[i][j] = min(sparseTable[i][j-1],sparseTable[i+(1<<(j-1))][j-1]);
            }
        }
    }

    public:
    SparseTable(vector<int>& nums){
        int n = nums.size();
        logTable.assign(n+1,0);
        for(int i=2; i<=n; ++i) logTable[i] = logTable[i/2]+1;
        create_sparseTable(nums);
    }

    int getMin(int l, int r){
        int log = logTable[r-l+1];
        return min(sparseTable[l][log],sparseTable[r-(1<<log)+1][log]);
    }

    void print_sparseTable(){
        for(auto &i : sparseTable){
            for(auto &j : i) cout<<j<<",";
            cout<<endl;
        }
    }
};
