// POI 2007 - Gas Pipelines
// Lúcio Cardoso

// Unchecked solution, since judge currently not working

#include <bits/stdc++.h>                                                        
                                                                                
using namespace std;                                                            
                                                                                
typedef long long ll;                                                           
typedef pair<int, int> pii;                                                     
                                                                                
const int maxn = 1e5+10;                                                        
                                                                                
vector<pii> a[maxn], b[maxn];                                                   
                                                                                
int main(void)                                                                  
{                                                                               
    int n;                                                                      
    scanf("%d", &n);                                                            
                                                                                
    ll ans = 0;                                                                 
                                                                                
    for (int i = 1; i <= n; i++)                                                
    {                                                                           
        int x, y;                                                               
        scanf("%d %d", &x, &y);                                                 
                                                                                
        a[x].push_back({y, i});                                                 
                                                                                
        ans += 1ll*(y-x);                                                       
    }                                                                           
                                                                                
    for (int i = 1; i <= n; i++)                                                
    {                                                                           
        int x, y;                                                               
        scanf("%d %d", &x, &y);                                                 
                                                                                
        b[x].push_back({y, i});                                                 
                                                                                
        ans += 1ll*(x-y);                                                       
    }                                                                           
                                                                                
    printf("%lld\n", ans);                                                      
                                                                                
    multiset<pii> st;                                                           
                                                                                
    for (int i = 0; i < maxn; i++)                                              
    {                                                                           
        sort(b[i].begin(), b[i].end());                                         
                                                                                
        for (auto pp: a[i])                                                     
            st.insert(pp);                                                      
                                                                                
        for (auto pp: b[i])                                                     
        {                                                                       
            int y = pp.first, ind = pp.second;                                  
                                                                                
            auto it = st.lower_bound({y, -1});                                  
                                                                                
            printf("%d %d\n", ind, it->second);                                 
                                                                                
            st.erase(it);                                                       
        }                                                                       
    }                                                                           
}
