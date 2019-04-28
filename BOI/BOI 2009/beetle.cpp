// BOI 2009 - Beetle
// Lúcio Cardoso

// Solution is the same as this one: 
// http://www.csc.kth.se/contest/boi/beetle-spoiler.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;
const int inf = 1e9+10;

int n, k;
int x[maxn], firstN, firstP; // first positions in array with neg/pos numbers

int dp[maxn][maxn];

int solve(int qtd, int pos)
{
	if (qtd == 0) return 0;
	if (dp[qtd][pos] != -1) return dp[qtd][pos];

	int ans = inf;

	if (pos <= firstN)
	{
		if (pos > 1)
			ans = min(ans, (x[pos]-x[pos-1])*qtd + solve(qtd-1, pos-1));

		int seen = k-qtd;
		int resta = seen-(firstN-pos+1);
		int nxt = firstP+resta;

		if (nxt <= n)
			ans = min(ans, (x[nxt]-x[pos])*qtd + solve(qtd-1, nxt));
	}
	else
	{
		if (pos < n)
			ans = min(ans, (x[pos+1]-x[pos])*qtd + solve(qtd-1, pos+1));

		int seen = k-qtd;
		int resta = seen-(pos-firstP+1);
		int nxt = firstN-resta;

		if (nxt >= 1)
			ans = min(ans, (x[pos]-x[nxt])*qtd + solve(qtd-1, nxt));
	}

	return dp[qtd][pos] = ans;
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]);

	sort(x+1, x+n+1);

	for (int i = 1; i <= n; i++)
		if (x[i] < 0) 
			firstN = i;

	firstP = firstN+1;

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		memset(dp, -1, sizeof dp);

		k = i;

		int aux1 = 1ll*k*m + k*x[firstN];
		int aux2 = 1ll*k*m - k*x[firstP];

		if (firstN >= 1) ans = max(ans, aux1-solve(k-1, firstN));

		if (firstP <= n) ans = max(ans, aux2-solve(k-1, firstP));
	}

	printf("%d\n", ans);
}
