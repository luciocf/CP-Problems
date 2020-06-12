// ICPC Swiss Subregional 2019 - G - Averaging the Average
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 35;
const int maxs = 110;
 
int n, k;
 
bool dp[maxs][maxn][maxs][maxn];
bool ant[maxs][maxn][maxs][maxn];
 
int a[maxn];
 
bool maior(pii a, pii b)
{
	return (a.ff*b.ss >= a.ss*b.ff);
 
}
 
bool igual(pii a, pii b)
{
	return (a.ff*b.ss == a.ss*b.ff);
}
 
pii soma(pii a, pii b)
{
	int g = __gcd(a.ff*b.ss + b.ff*a.ss, a.ss*b.ss);
 
	return {(a.ff*b.ss + b.ff*a.ss)/g, (a.ss*b.ss)/g};
}
 
pii sub(pii a, pii b)
{
	int g = __gcd(a.ff*b.ss + b.ff*a.ss, a.ss*b.ss);
 
	return {(a.ff*b.ss - b.ff*a.ss)/g, (a.ss*b.ss)/g};
}
 
int main(void)
{
	scanf("%d %d", &n, &k);
 
	int tot = 0;
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
 
		tot += a[i];
	}
 
	dp[0][0][0][0] = true;
 
	for (int i = 1; i <= n; i++)
	{
		for (int s1 = 0; s1 <= 100; s1++)
			for (int t1 = 0; t1 <= n; t1++)
				for (int s2 = 0; s2 <= 100; s2++)
					for (int t2 = 0; t2 <= n; t2++)
						ant[s1][t1][s2][t2] = dp[s1][t1][s2][t2];
 
		for (int s1 = 0; s1 <= 100; s1++)
		{
			for (int t1 = 0; t1 <= n; t1++)
			{
				for (int s2 = 0; s2 <= 100; s2++)
				{
					for (int t2 = 0; t2 <= n; t2++)
					{
						if (s1+a[i] <= 100) dp[s1+a[i]][t1+1][s2][t2] |= ant[s1][t1][s2][t2];
						if (s2+a[i] <= 100) dp[s1][t1][s2+a[i]][t2+1] |= ant[s1][t1][s2][t2];
					}
				}
			}
		}
	}
 
	pii best = {1000, 1};
	pii f = {k, 1};
 
	for (int s1 = 1; s1 <= 100; s1++)
	{
		for (int t1 = 1; t1 <= n; t1++)
		{
			for (int s2 = 1; s2 <= 100; s2++)
			{
				for (int t2 = 1; t2 <= n; t2++)
				{
					if (t1+t2 >= n || !dp[s1][t1][s2][t2]) continue;
 
					int s3 = tot-s1-s2;
					int t3 = n-t1-t2;
 
					pii aux = soma({s1, t1}, {s2, t2});
					aux = soma(aux, {s3, t3});
 
					aux.ss *= 3;
 
					if (maior(aux, f))
					{
						if (maior(best, f))
						{
							if (!maior(sub(aux, f), sub(best, f)) || (igual(sub(aux, f), sub(best, f)) && !maior(aux, best)))
								best = aux;
						}
						else
						{
							if (!maior(sub(aux, f), sub(f, best)) || (igual(sub(aux, f), sub(f, best)) && !maior(aux, best)))
								best = aux;
						}
					}
					else
					{
						if (maior(best, f))
						{
							if (!maior(sub(f, aux), sub(best, f)) || (igual(sub(f, aux), sub(best, f)) && !maior(aux, best)))
								best = aux;
						}
						else
						{
							if (!maior(sub(f, aux), sub(f, best)) || (igual(sub(f, aux), sub(f, best)) && !maior(aux, best)))
								best = aux;
						}
					}
				}
			}
		}
	}
 
	int g = __gcd(best.ff, best.ss);
 
	printf("%d/%d\n", best.ff/g, best.ss/g);
}
