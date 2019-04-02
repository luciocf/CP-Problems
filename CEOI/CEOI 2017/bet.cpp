// CEOI 2017 - Sure Bet
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;

double a[maxn], b[maxn];
double s[2][maxn];

int busca(int k, bool q)
{
	int ini = 1, fim = n, ans = n;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (s[q][k] <= s[!q][mid]) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

bool comp(double a, double b) {return a > b;}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lf %lf", &a[i], &b[i]);

	sort(a+1, a+n+1, comp);
	sort(b+1, b+n+1, comp);

	for (int i = 1; i <= n; i++)
	{
		s[0][i] = s[0][i-1]+a[i];
		s[1][i] = s[1][i-1]+b[i];
	}

	double ans = 0.00;

	for (int i = 1; i <= n && s[0][i] <= s[1][n]; i++)
		ans = max(ans, s[0][i]-i-busca(i, 0));

	for (int i = 1; i <= n && s[1][i] <= s[0][n]; i++)
		ans = max(ans, s[1][i]-i-busca(i, 1));

	printf("%.4lf\n", ans);
}
