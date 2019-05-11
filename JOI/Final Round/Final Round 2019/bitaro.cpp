// JOI Final Round 2019 - Bitaro the Brave
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 3e3+10;
 
int prefL[maxn][maxn], prefC[maxn][maxn];
 
char tab[maxn][maxn];
 
int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			prefL[i][j] = prefL[i][j-1];
 
			if (tab[i][j] == 'O')
				prefL[i][j]++;
		}
	}
 
	for (int j = 1; j <= m; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			prefC[i][j] = prefC[i-1][j];
 
			if (tab[i][j] == 'I')
				prefC[i][j]++;
		}
	}
 
	long long ans = 0ll;
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (tab[i][j] == 'J')
				ans += 1ll*(prefL[i][m]-prefL[i][j])*(prefC[n][j]-prefC[i][j]);
 
	printf("%lld\n", ans);
}
