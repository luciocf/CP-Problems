// CSES 1660 - Subarray Sums I
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e5+10;
 
typedef long long ll;
 
int a[maxn];
 
int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
 
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
 
    map<ll, int> mp;
 
    ll soma = 0;
    ll ans = 0ll;
 
    mp[0] = 1;
 
    for (int i = 1; i <= n; i++)
    {
        soma += 1ll*a[i];
 
        if (soma >= k)
            ans += 1ll*mp[soma-k];
 
        mp[soma]++;
    }
 
    printf("%lld\n", ans);
}
