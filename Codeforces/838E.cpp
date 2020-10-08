// Codeforces 838E - Convex Contour
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2510;

int n;
int x[maxn], y[maxn];

double dp[maxn][maxn][2];
bool mark[maxn][maxn][2];

double dist(int i, int j)
{
	double dx = x[i]-x[j];
	double dy = y[i]-y[j];

	return sqrt(dx*dx + dy*dy);
}

int qtd(int i, int j)
{
	if (i < j) return j-i+1;
	return (n - (i-j) + 1);
}

double solve(int i, int j, int q)
{
	if (qtd(i, j) == n) return 0;
	if (mark[i][j][q]) return dp[i][j][q];

	mark[i][j][q] = 1;

	double ans = 0;

	if (q == 0)
	{
		ans = max(ans, solve((i+n-1)%n, j, 0) + dist(i, (i+n-1)%n));
		ans = max(ans, solve(i, (j+1)%n, 1) + dist(i, (j+1)%n));
	}
	else
	{
		ans = max(ans, solve((i+n-1)%n, j, 0) + dist(j, (i+n-1)%n));
		ans = max(ans, solve(i, (j+1)%n, 1) + dist(j, (j+1)%n));
	}

	return dp[i][j][q] = ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);

	double ans = 0;

	for (int i = 0; i < n; i++)
		ans = max(ans, dist(i, (i+1)%n) + max(solve(i, (i+1)%n, 0), solve(i, (i+1)%n, 1)));

	printf("%.9lf\n", ans);
}
