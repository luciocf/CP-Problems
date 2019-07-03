// USACO Plat Dec 2015 - High Card Low Card
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], b[maxn];

int pref[maxn], suf[maxn];

int main(void)
{
	FILE *fin = fopen("cardgame.in", "r");
	FILE *fout = fopen("cardgame.out", "w");

	int n;
	fscanf(fin, "%d", &n);

	set<int> st1, st2;

	for (int i = 1; i <= 2*n; i++)
		st1.insert(i), st2.insert(i);

	for (int i = 1; i <= n; i++)
	{
		fscanf(fin, "%d", &b[i]);
		st1.erase(b[i]), st2.erase(b[i]);
	}

	for (int i = 1; i <= n; i++)
	{
		pref[i] = pref[i-1];

		if (st1.upper_bound(b[i]) != st1.end())
		{
			pref[i]++;
			st1.erase(st1.upper_bound(b[i]));
		}
	}

	for (int i = n; i >= 1; i--)
	{
		suf[i] = suf[i+1];

		set<int>::iterator it = st2.upper_bound(b[i]);

		if (it != st2.begin())
		{
			suf[i]++;
			st2.erase(--it);
		}
	}

	int ans = 0;
	for (int i = 0; i <= n; i++)
		ans = max(ans, pref[i]+suf[i+1]);

	fprintf(fout, "%d\n", ans);
}
