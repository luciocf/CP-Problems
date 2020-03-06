// Codeforces 1209G1 - Into Blocks (easy version)
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int a[maxn];

int fq[maxn];

int mn[maxn], mx[maxn];

vector<pii> range;

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		fq[a[i]]++;

		if (mn[a[i]] == 0) mn[a[i]] = i;
		mx[a[i]] = i;
	}

	for (int i = 1; i < maxn; i++)
		if (mn[i])
			range.push_back({mn[i], mx[i]});

	sort(range.begin(), range.end());

	int ans = 0;

	for (int i = 0; i < range.size(); i++)
	{
		int l = range[i].first;
		int r = range[i].second;

		int j;
		for (j = i+1; j < range.size(); j++)
		{
			if (range[j].second <= r) continue;
			if (range[j].first > r) break;

			r = range[j].second;
		}
		j--;

		int maior = 0;

		for (int k = l; k <= r; k++)
			maior = max(maior, fq[a[k]]);

		ans += (r-l+1 - maior);
		i = j;
	}

	printf("%d\n", ans);
}
