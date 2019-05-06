// USACO 2018/2019 Gold - Sleepy Cow Sorting
// Lúcio Cardoso

// Solution is the same as this one: http://usaco.org/current/data/sol_sleepy_gold_jan19.html

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn];

int bit[maxn];

void upd(int x, int v)
{
	for (; x <= n; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];

	return ans;
}

int main(void)
{
	FILE *fin = fopen("sleepy.in", "r");
	FILE *fout = fopen("sleepy.out", "w");

	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	int last = 0;
	for (int i = n; i > 1; i--)
	{
		if (a[i-1] > a[i])
		{
			last = i-1;
			break;
		}
	}

	fprintf(fout, "%d\n", last);

	for (int i = last+1; i <= n; i++)
		upd(a[i], 1);

	for (int i = 1; i <= last; i++)
	{
		fprintf(fout, "%d", (last-i) + soma(a[i]-1));
		if (i != last) fprintf(fout, " ");

		upd(a[i], 1);
	}

	fprintf(fout, "\n");
}
