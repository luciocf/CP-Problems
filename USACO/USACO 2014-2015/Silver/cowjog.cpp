// USACO 2014-2015 - Cow Jog
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], b[maxn];

int main(void)
{
	FILE *fin = fopen("cowjog.in", "r");
	FILE *fout = fopen("cowjog.out", "w");

	int n, T;
	fscanf(fin, "%d %d", &n, &T);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &a[i], &b[i]);

	int last = n, ans = 1;

	for (int i = n-1; i >= 1; i--)
	{
		if (1ll*a[i] + 1ll*b[i]*T < 1ll*a[last] + 1ll*b[last]*T)
		{
			ans++;
			last = i;
		}
	}

	fprintf(fout, "%d\n", ans);
}
