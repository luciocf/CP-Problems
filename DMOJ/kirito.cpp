// DMOJ - Kirito
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;
const int maxm = 5e3+10;

const int mod = 1e9+7;
const int P = 31;

int n, m;
char a[maxn][maxm];

int ind[maxn];

int pot[maxm];
int h[maxn][maxm];

void get_h(int i)
{
	for (int j = 1; j <= m; j++)
	{
		int c = (a[i][j]-'0'+1);

		h[i][j] = (h[i][j-1] + (1ll*pot[j-1]*c)%mod)%mod;
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;

	pot[0] = 1;
	for (int i = 1; i < m; i++)
		pot[i] = (1ll*P*pot[i-1])%mod;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];

	for (int i = 1; i <= n; i++)
	{
		ind[i] = i;
		get_h(i);
	}

	int q;
	cin >> q;

	while (q--)
	{
		int l, r;
		cin >> l >> r;

		int ptr = m;

		for (int i = l+1; i <= r; i++)
			while (h[ind[i]][ptr] != h[ind[i-1]][ptr])
				ptr--;

		cout << (r-l+1)*ptr << "\n";

		swap(ind[l], ind[r]);
	}
}
