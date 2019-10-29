// CEOI 2012 - Jobs Scheduling
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;

int n, d, m;
pii a[maxn];

bool ok(int x)
{
	int cur_d = 1;

	for (int i = 1; i <= m; i++)
	{
		int j = i;
		for (; j <= m && a[j].ff <= cur_d && j-i+1 <= x; j++)
			if (cur_d > a[j].ff+d)
				return 0;

		i = j-1;
		cur_d++;
	}

	return 1;
}

int busca(void)
{
	int ini = 1, fim = m, ans = m;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &d, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	sort(a+1, a+m+1);

	int ans = busca();
	printf("%d\n", ans);

	int cur_d = 1, ind = 1;

	for (int i = 1; i <= n; i++)
	{
		int ant = ind;

		for (; ind <= m && a[ind].ff <= cur_d && ind-ant+1 <= ans; ind++)
			printf("%d ", a[ind].ss);
		printf("0\n");

		cur_d++;
	}
}
