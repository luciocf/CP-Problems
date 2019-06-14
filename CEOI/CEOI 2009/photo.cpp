// CEOI 2009 - Photo
// Lúcio Cardoso

// Same solution as the one presented here: http://www.infosb.net/ceoi2009/view_page.php?id=24 (the document with all solutions)

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
const int maxn = 110;
 
typedef pair<int, int> pii;
 
int n, A;
pii p[maxn];
 
int Left[maxn][maxn], Right[maxn][maxn], Down[maxn][maxn];
int nxt[maxn][maxn];
int dp[maxn][maxn][maxn];
 
bool rectangle(int h, int w)
{
	return (1ll*h*w <= 1ll*A);
}
 
int solve(int l, int r, int h)
{
	if (p[l].ff > p[r].ff || l == n+1 || r == n+1) return 0;
	if (dp[l][r][h] != -1) return dp[l][r][h];
 
	int ans = n+1;
 
	for (int i = l; i <= r; i++)
		if (rectangle(p[i].ff-p[l].ff, max(p[l].ss, p[i].ss)))
			ans = min(ans, 1+solve(Left[l][i], Right[l][i], Down[l][i])+solve(nxt[i][h], r, h));
 
	return dp[l][r][h] = ans;
}
 
int main(void)
{
	scanf("%d %d", &n, &A);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].ff, &p[i].ss);
 
	sort(p+1, p+n+1);
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{	
			nxt[i][j] = n+1;
			for (int l = i+1; l <= n; l++)
			{
				if (p[l].ff > p[i].ff && p[l].ss > p[j].ss)
				{
					nxt[i][j] = l;
					break;
				}
			}
		}
	}
 
	for (int l = 1; l <= n; l++)
	{
		for (int r = l; r <= n; r++)
		{
			if (!rectangle(p[r].ff-p[l].ff, max(p[l].ss, p[r].ss))) continue;
 
			Left[l][r] = Right[l][r] = Down[l][r] = n+1;
 
			for (int i = l; i <= r; i++)
			{
				int h = max({p[l].ss, p[r].ss, p[i].ss});
 
				if (rectangle(p[r].ff-p[l].ff, h))
					if (h > p[Down[l][r]].ss)
						Down[l][r] = i;
			}
 
			for (int i = l; i < nxt[r][r]; i++)
			{
				if (p[i].ss > p[Down[l][r]].ss)
				{
					if (Left[l][r] == n+1)
						Left[l][r] = i;
 
					Right[l][r] = i;
				}
			}
		}
	}
 
	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(1, n, 0));
}
