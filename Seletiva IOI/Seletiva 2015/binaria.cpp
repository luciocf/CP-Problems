// Seletiva IOI 2015 - Binária
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int mod = 1e9+7;

int N, K, H;

int ans, ate;

int L[maxn], R[maxn];

int val[maxn];

int fat[maxn], dp[maxn][maxn];

int mult(int a, int b)
{
	return (1ll*a*b)%mod;
}

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return mult(a, mult(t, t));
	return mult(t, t);
}

int choose(int a, int b)
{
	return mult(fat[a], pot(mult(fat[b], fat[a-b]), mod-2));
}

int solve(int n, int h)
{
	if (n == 0) return 1;
	if (h > H) return 0;
	if (dp[n][h] != -1) return dp[n][h];

	int ans = 0;

	for (int i = 1; i <= n; i++)
		ans = (1ll*ans + (1ll*choose(n-1, i-1)*mult(solve(i-1, h+1), solve(n-i, h+1)))%mod)%mod;

	return dp[n][h] = ans;
}

void insert(int u, int x)
{
	if (x > u)
	{
		if (R[u]) insert(R[u], x);
		else R[u] = x;
	}
	else
	{
		if (L[u]) insert(L[u], x);
		else L[u] = x;
	}
}

void dfs(int u, int l, int r, int nivel)
{
	val[u] = u-l+1;

	if (L[u])
		dfs(L[u], l, u-1, nivel+1);
	else
	{
		ans = mult(ans, mult(choose(N-ate, val[u]-1), solve(val[u]-1, nivel+1)));
		ate += val[u]-1;
	}

	if (R[u])
		dfs(R[u], u+1, r, nivel+1);
	else
	{
		ans = mult(ans, mult(choose(N-ate, r-l+1-val[u]), solve(r-l+1-val[u], nivel+1)));
		ate += (r-l+1-val[u]);
	}
}

int get(int root)
{
	ate = K, ans = 1;

	memset(dp, -1, sizeof dp);

	dfs(root, 1, N, 1);

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &N, &K, &H);
	ate = K;

	fat[0] = 1;
	for (int i = 1; i <= N; i++)
		fat[i] = (1ll*fat[i-1]*i)%mod;

	if (K == 0)
	{
		memset(dp, -1, sizeof dp);

		int R = solve(N, 1);

		H--;
		memset(dp, -1, sizeof dp);

		int L = solve(N, 1);

		printf("%d\n", (R-L+mod)%mod);
		return 0;
	}

	int root = 0;

	for (int i = 1; i <= K; i++)
	{
		int x;
		scanf("%d", &x);

		if (i == 1) root = x;

		if (i > 1) insert(root, x);
	}

	int R = get(root);

	H--;

	int L = get(root);

	printf("%d\n", (R-L+mod)%mod);
}
