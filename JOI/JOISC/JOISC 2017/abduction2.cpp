// JOISC 2017 - Abduction 2
// Lúcio Cardoso

/* Solution:
	
	Let dp[i][j][0/1] be the maximum possible distance attainable by starting at (i, j) walking
	either horizontally or vertically (0 = horizontally, 1 = vertically).

	Let's calculate dp[i][j][0] (dp[i][j][1] can be calculated analogously). Notice that if we leave
	the position (i, j) by walking to the left, we're either going to turn veritcally at the rightmost
	position with value greater than A[i] or we're simply going to walk i-1 times to the left. The same
	observation can be applied when walking to the right.

	Thus, we can get a solution by simply finding such "closest value greater than a value" and recursing/memoizing
	appropriately. This can be done by using a sparse table/segment tree in O(log n). Thus, this solution has complexity
	O(nm log n).

	To improve upon it, notice there are not many recursive calls in such DP. As a matter of fact, there are O(H+W) calls.
	Hence, to optimize memory, we can use our dp table as a map.

	Final complexity is O((n+m) log n).

*/

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 5e4+10;
const int maxl = 18;
 
int n, m;
int a[2][maxn];
 
map<int, ll> dp[maxn][2];
 
struct SparseTable
{
	int tab[2][2][maxn][maxl];
 
	void build(void)
	{
		for (int i = 1; i <= n; i++)
		{
			if (i > 1) tab[0][0][i][0] = a[0][i-1];
 
			if (i < n) tab[0][1][i][0] = a[0][i+1];
		}
 
		for (int i = 1; i <= m; i++)
		{
			if (i > 1) tab[1][0][i][0] = a[1][i-1];
 
			if (i < m) tab[1][1][i][0] = a[1][i+1];
		}
 
		for (int j = 1; j < maxl; j++)
		{
			for (int i = 1; i <= n; i++)
			{
				if (i-(1<<j) > 0)
					tab[0][0][i][j] = max(tab[0][0][i][j-1], tab[0][0][i-(1<<(j-1))][j-1]);
 
				if (i+(1<<j) <= n)
					tab[0][1][i][j] = max(tab[0][1][i][j-1], tab[0][1][i+(1<<(j-1))][j-1]);
			}
 
			for (int i = 1; i <= m; i++)
			{
				if (i-(1<<j) > 0)
					tab[1][0][i][j] = max(tab[1][0][i][j-1], tab[1][0][i-(1<<(j-1))][j-1]);
 
				if (i+(1<<j) <= m)
					tab[1][1][i][j] = max(tab[1][1][i][j-1], tab[1][1][i+(1<<(j-1))][j-1]);
			}
		}
	}
 
	int get_l(int pos, int x, int q)
	{
		for (int i = maxl-1; i >= 0; i--)
			if (pos-(1<<i) > 0 && tab[q][0][pos][i] < x)
				pos -= (1<<i);
 
		return pos-1;
	}
 
	int get_r(int pos, int x, int q)
	{
		for (int i = maxl-1; i >= 0; i--)
			if (pos+(1<<i) <= (!q ? n : m) && tab[q][1][pos][i] < x)
				pos += (1<<i);
 
		return pos+1;
	}
} ST;
 
ll solve(int i, int j, int q)
{
	if (dp[i][q].find(j) != dp[i][q].end()) return dp[i][q][j];
 
	ll ans;
 
	if (!q)
	{
		int l = ST.get_l(j, a[0][i], 1), r = ST.get_r(j, a[0][i], 1);
 
		if (l == 0 && r == m+1) ans = max(j-1, m-j);
		else if (l == 0) ans = max(1ll*(j-1), (1ll*(r-j) + solve(i, r, 1)));
		else if (r == m+1) ans = max(1ll*(m-j), (1ll*(j-l) + solve(i, l, 1)));
		else ans = max(1ll*(r-j) + solve(i, r, 1), 1ll*(j-l) + solve(i, l, 1));
	}
	else
	{
		int l = ST.get_l(i, a[1][j], 0), r = ST.get_r(i, a[1][j], 0);
 
		if (l == 0 && r == n+1) ans = max(i-1, n-i);
		else if (l == 0) ans = max(1ll*(i-1), 1ll*(r-i) + solve(r, j, 0));
		else if (r == n+1) ans = max(1ll*(n-i), (1ll*(i-l) + solve(l, j, 0)));
		else ans = max(1ll*(r-i) + solve(r, j, 0), 1ll*(i-l) + solve(l, j, 0));
	}
 
	return dp[i][q][j] = ans;
}
 
int main(void)
{
	int q;
	scanf("%d %d %d", &n, &m, &q);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[0][i]);
 
	for (int i = 1; i <= m; i++)
		scanf("%d", &a[1][i]);
 
	ST.build();
 
	while (q--)
	{
		int i, j;
		scanf("%d %d", &i, &j);

		printf("%lld\n", max(solve(i, j, 0), solve(i, j, 1)));
	}
}
