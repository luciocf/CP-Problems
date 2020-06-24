// CEOI 2019 - Cubeword
// Lúcio Cardoso

// Solution is the same as in editorial in CF

#include <bits/stdc++.h>

#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

const int maxn = 62;
const int mod = 998244353;

int cnt[8][maxn][maxn];
int qtd[8][maxn][maxn][maxn];

inline int get(char c)
{
	if (c >= 'a' && c <= 'z') return (int)(c-'a');
	if (c >= 'A' && c <= 'Z') return (int)(c-'A')+26;
	return (int)(c-'0')+52;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	map<string, bool> mark;

	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;

		if (!mark[s])
			cnt[s.size()-3][get(s[0])][get(s.back())]++;

		mark[s] = true;

		reverse(s.begin(), s.end());

		if (!mark[s])
			cnt[s.size()-3][get(s[0])][get(s.back())]++;

		mark[s] = true;
	}

	for (int sz = 0; sz < 8; sz++)
		for (int a = 0; a < 62; a++)
			for (int b = a; b < 62; b++)
				for (int c = b; c < 62; c++)
					for (int d = 0; d < 62; d++)
						qtd[sz][a][b][c] = (1ll*qtd[sz][a][b][c] + 1ll*cnt[sz][d][a]*cnt[sz][d][b]*cnt[sz][d][c])%mod;

	int ans = 0;

	for (int sz = 0; sz < 8; sz++)
	{
		for (int a = 0; a < 62; a++)
		{
			for (int b = a; b < 62; b++)
			{
				for (int c = b; c < 62; c++)
				{
					for (int d = c; d < 62; d++)
					{
						int p1 = (1ll*qtd[sz][a][c][d]*qtd[sz][b][c][d])%mod;
						int p2 = (1ll*qtd[sz][a][b][d]*qtd[sz][a][b][c])%mod;

						int k = (1ll*p1*p2)%mod, mult = 24;

						if (a == b && b == c && c == d) mult /= 24;
						else if (a == b && b == c) mult /= 6;
						else if (a == b)
						{
							mult /= 2;
							if (c == d) mult /= 2;
						}
						else
						{
							if (b == c && c == d) mult /= 6;
							else if (b == c) mult /= 2;
							else if (c == d) mult /= 2;
						}

						ans = (ans + (1ll*mult*k)%mod)%mod;
					}
				}
			}
		}
	}

	printf("%d\n", ans);
}
