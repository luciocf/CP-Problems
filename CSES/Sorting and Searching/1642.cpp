// CSES 1642 - Sum of Four Values
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e3+10;
 
int a[maxn];
 
map<int, pii> mp;
 
int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);
	
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	int ind1 = -1, ind2 = -1, ind3 = -1, ind4 = -1;
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = i+1; j <= n; j++)
		{
			int soma = a[i]+a[j];
 
			if (soma < x && mp.find(x-soma) != mp.end())
			{
				ind1 = i, ind2 = j;
				ind3 = mp[x-soma].first, ind4 = mp[x-soma].second;
			}
		}
 
		for (int j = 1; j < i; j++)
			mp[a[i]+a[j]] = {j, i};
	}
 
	if (ind1 == -1) printf("IMPOSSIBLE\n");
	else printf("%d %d %d %d", ind1, ind2, ind3, ind4);
}
