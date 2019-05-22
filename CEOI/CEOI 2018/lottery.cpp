// CEOI 2018 - Lottery
// Lúcio Cardoso

// Solution is explained here: https://codeforces.com/blog/entry/61181?#comment-451309

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e4+10;
const int maxq = 110;

typedef pair<int, int> pii;

int a[maxn];

int first[maxn];
int ans[maxn][maxq];

pii query[maxq];

int main(void)
{
	int n, l;
	scanf("%d %d", &n, &l);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d", &query[i].ff);
		query[i].ss = i;
	}

	sort(query+1, query+q+1);

	for (int i = 0; i <= l; i++)
	{
		first[i] = q+1;

		for (int j = 1; j <= q; j++)
		{
			if (query[j].ff >= i)
			{
				first[i] = query[j].ss;
				break;
			}
		}
	}

	for (int i = 1; i+l-1 <= n; i++)
	{
		int at = 0;
		for (int j = 1; j <= l; j++)
			if (a[i+j-1] != a[j])
				at++;

		if (i != 1)
		{
			ans[1][first[at]]++;
			ans[i][first[at]]++;
		}

		for (int j = 2; j+l-1 <= n; j++)
		{
			int pos = i+j-1;
			if (pos+l-1 > n) break;

			if (a[j-1] != a[pos-1]) at--;

			if (a[j+l-1] != a[pos+l-1]) at++;

			if (j != pos)
			{
				ans[j][first[at]]++;
				ans[pos][first[at]]++;
			}
		}
	}

	for (int i = 1; i <= q; i++)
		for (int j = 1; j <= n; j++)
			ans[j][query[i].ss] += ans[j][query[i-1].ss];

	for (int i = 1; i <= q; i++)
	{
		for (int j = 1; j <= n-l+1; j++)
		{
			if (j == n-l+1) printf("%d\n", ans[j][i]);
			else printf("%d ", ans[j][i]);
		}
	}
}
