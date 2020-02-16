// Codeforces 1172D - Nauuo and Portals
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1100;

int n;
int a[maxn][maxn], b[maxn][maxn];

int a_inv[maxn], b_inv[maxn];

vector<pair<pii, pii>> ans;

void solve(int k)
{
	if (k == n) return;

	ans.push_back({{k, b_inv[k]}, {a_inv[k], k}});

	a[a_inv[k]][k+1] = a[k][k];
	b[k+1][b_inv[k]] = b[k][k];

	for (int i = k+1; i <= n; i++)
	{
		if (i != a_inv[k]) a[i][k+1] = a[i][k];
		if (i != b_inv[k]) b[k+1][i] = b[k][i];

		if (a[i][k+1] == k+1) a_inv[k+1] = i;
		if (b[k+1][i] == k+1) b_inv[k+1] = i;
	}

	solve(k+1);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i][1]);

		if (a[i][1] == 1) a_inv[1] = i;
	}

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[1][i]);

		if (b[1][i] == 1) b_inv[1] = i; 
	}

	solve(1);

	int tot = 0;
	for (auto p: ans)
		if (p.first != p.second)
			++tot;

	printf("%d\n", tot);
	for (auto p: ans)
		if (p.first != p.second)
			printf("%d %d %d %d\n", p.first.first, p.first.second, p.second.first, p.second.second);
}
