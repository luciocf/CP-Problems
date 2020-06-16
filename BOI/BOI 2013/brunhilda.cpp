// BOI 2013 - Brunhilda’s Birthday
// Lúcio Cardoso

// Solution is the same as the model solution in editorial : https://github.com/mostafasaad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2013_solutions/brunhilda-sol.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxv = 1e7+10;

int p[maxn];

int prox[maxv], dp[maxv];

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	int prod = 1;

	for (int i = 0; i < maxv; i++)
		prox[i] = 2*maxv;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &p[i]);
			
		if (prod != maxv)
		{
			if (1ll*prod*p[i] > 1ll*maxv)
				prod = maxv;
			else
				prod *= p[i];
		}

		for (int j = 0; j < maxv; j += p[i])
		{
			int a = min(maxv-1, j+p[i]-1);

			prox[a] = min(prox[a], j);
		}
	}


	for (int i = maxv-2; i >= 0; i--)
		prox[i] = min(prox[i], prox[i+1]);

	for (int i = 1; i < maxv; i++)
		dp[i] = dp[prox[i]] + 1;

	while (q--)
	{
		int x;
		scanf("%d", &x);

		if (prod <= x)
		{
			printf("oo\n");
			continue;
		}

		printf("%d\n", dp[x]);
	}
}
