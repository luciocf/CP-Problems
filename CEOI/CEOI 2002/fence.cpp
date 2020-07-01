// CEOI 2002 - Fence
// Lúcio Cardoso

// Solution is the same as in: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Fence/main.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 25;

int n, m;
ll k;

int a[maxn];

bool mark[maxn];

ll dp[maxn][maxn][2];

ll solve(int i, int qtd_menor, int flag)
{
	if (i == m) return 1;
	if (dp[i][qtd_menor][flag] != -1) return dp[i][qtd_menor][flag];

	int qtd_maior = m-i-qtd_menor;
	ll ans = 0;

	if (flag == 0)
	{
		for (int j = 1; j <= qtd_menor; j++)
			ans += solve(i+1, j-1, 1);
	}
	else
	{
		for (int j = 1; j <= qtd_maior; j++)
			ans += solve(i+1, qtd_menor+j-1, 0);
	}

	return dp[i][qtd_menor][flag] = ans;
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		memset(mark, 0, sizeof mark);

		scanf("%d %lld", &n, &k);

		m = n;

		int prev = -1, ant = -1;

		for (int i = 1; i <= n; i++)
		{
			int qtd = 0, ans;

			memset(dp, -1, sizeof dp);

			for (int j = 1; j <= n; j++)
			{
				if (mark[j]) continue;

				if (prev == 1 && j <= ant)
				{
					++qtd;
					continue;
				}

				if (prev == -1)
				{
					if (solve(1, qtd, 0) >= k)
					{
						ans = j, prev = 0;
						break;
					}

					k -= solve(1, qtd, 0);
	
					if (solve(1, qtd, 1) >= k)
					{
						ans = j, prev = 1;
						break;
					}

					k -= solve(1, qtd, 1);
				}
				else
				{
					if (prev == 1 && solve(1, qtd, 0) >= k)
					{
						ans = j, prev = 0;
						break;
					}

					if (prev == 0 && solve(1, qtd, 1) >= k)
					{
						ans = j, prev = 1;
						break;
					}

					if (prev == 0) k -= solve(1, qtd, 1);
					else k -= solve(1, qtd, 0);
				}

				++qtd;
			}

			printf("%d ", ans);
			--m, mark[ans] = true, ant = ans;
		}
		printf("\n");
	}
}
