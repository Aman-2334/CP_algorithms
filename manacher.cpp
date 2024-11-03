#include <bits/stdc++.h>
using namespace std;

class Manacher{
    string t;
    vector<int> p;
    public:
    Manacher(string &s):p(2*s.size()+1){
        for(char c : s){
            t += string("#") + c;
        }
        t += '#';
        preprocess();
    }

    void preprocess(){
        int l=0,r=0,n=t.size();
        for(int i=0; i<n; ++i){
            p[i] = max(0,min(r-i,p[l+r-i]));
            while(i-p[i] >= 0 && i+p[i] < n && t[i-p[i]] == t[i+p[i]]) p[i]++;
            if(i+p[i] > r){
                l = i-p[i]; r = i+p[i];
            }
        }
    }

    int getLongest(int cen, bool odd){
        int pos = 2*cen+1+(!odd);
        return p[pos]-1;
    }

    bool checkPalindrome(int l, int r){
        if((r-l+1) <= getLongest((l+r)/2,l%2 == r%2)) return true;
        return false;
    }
};