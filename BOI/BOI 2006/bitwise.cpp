// BOI 2006 - Bitwise Expressions
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

int l[maxn], r[maxn];

int ind_l[maxn], ind_r[maxn];

bool ok[maxn][32];

int main(void)
{
	int n, g;
	scanf("%d %d", &n, &g);

	for (int i = 1; i <= g; i++)
	{
		int x;
		scanf("%d", &x);

		ind_l[i] = ind_r[i-1]+1;
		ind_r[i] = ind_l[i]+x-1;
	}

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &l[i], &r[i]);

	int ans = 0;

	for (int b = 30; b >= 0; b--)
	{
		bool deu = 1;

		for (int i = 1; i <= g; i++)
		{
			if (ok[i][b]) continue;

			bool tem = 0;

			for (int j = ind_l[i]; j <= ind_r[i]; j++)
				if (r[j] >= (1<<b))
					tem = 1;

			if (!tem) deu = 0;
		}

		if (!deu)
		{
			for (int i = 1; i <= n; i++)
				if (r[i] >= (1<<b) && l[i] >= (1<<b))
					l[i] ^= (1<<b), r[i] ^= (1<<b);

			continue;
		}

		ans |= (1<<b);

		for (int i = 1; i <= g; i++)
		{
			if (ok[i][b]) continue;
			ok[i][b] = 1;

			bool tem_tudo = 0;

			for (int j = ind_l[i]; j <= ind_r[i]; j++)
				if (b < 30 && r[j] >= (1<<(b+1))-1)
					tem_tudo = 1;

			if (tem_tudo)
			{
				for (int j = b; j >= 0; j--)
					ok[i][j] = 1;
				continue;
			}

			bool todos = 1;

			for (int j = ind_l[i]; j <= ind_r[i]; j++)
				if (r[j] >= (1<<b) && l[j] <= (1<<b)-1)
					todos = 0;

			if (todos)
			{
				for (int j = ind_l[i]; j <= ind_r[i]; j++)
					if (r[j] >= (1<<b))
						l[j] ^= (1<<b), r[j] ^= (1<<b);

				continue;
			}

			int qtd = 0;
			for (int j = ind_l[i]; j <= ind_r[i]; j++)
				if (r[j] >= (1<<b))
					++qtd;

			if (qtd == 1)
			{
				for (int j = ind_l[i]; j <= ind_r[i]; j++)
					if (r[j] >= (1<<b))
						l[j] = 0, r[j] ^= (1<<b);
			}
			else
			{
				for (int j = b; j >= 0; j--)
					ok[i][j] = 1;
			}
		}
	}

	printf("%d\n", ans);
}
