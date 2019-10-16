// USACO 2015/2016 - Fenced In
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 3e4+10;

int A, B, n, m;
int a[maxn], b[maxn];

vector<pii> edge;

void get_edge(void)
{
	edge.push_back({a[1], 0});
	edge.push_back({A-a[n], 0});

	for (int i = 2; i <= n; i++)
		edge.push_back({a[i]-a[i-1], 0});

	edge.push_back({b[1], 1});
	edge.push_back({B-b[m], 1});

	for (int i = 2; i <= m; i++)
		edge.push_back({b[i]-b[i-1], 1});

	sort(edge.begin(), edge.end());
}

int main(void)
{
	freopen("fencedin.in", "r", stdin);
	freopen("fencedin.out", "w", stdout);

	scanf("%d %d %d %d", &A, &B, &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	sort(a+1, a+n+1); sort(b+1, b+m+1);

	get_edge();

	int tot = n*m + n + m;
	int qtd_0 = 0, qtd_1 = 0;
	int last = 0;
	ll ans = 0;

	for (int i = 0; i < edge.size(); i++)
	{
		pii pp = edge[i];

		int d = pp.first, qtd = (pp.second == 0 ? m : n);
		int r = min(tot, qtd);

		ans += 1ll*r*d;
		tot -= r;

		if (tot == 0)
		{
			printf("%lld\n", ans);
			return 0;
		}

		if (pp.second == 0) qtd_0++;
		else qtd_1++;

		if (max(qtd_0, qtd_1) > 1 && min(qtd_0, qtd_1) > 0)
		{
			last = i+1;
			break;
		}
	}

	for (int i = last; i < edge.size(); i++)
	{
		pii pp = edge[i];

		int d = pp.first;
		int r = tot;

		if (pp.second == 0)
		{
			int r = min({m-(qtd_1-1), tot});

			if (r > 0)
			{
				ans += 1ll*r*d;
				tot -= r;
				qtd_0++;
			}
		}
		else
		{
			int r = min(n-(qtd_0-1), tot);

			if (r > 0)
			{
				ans += 1ll*r*d;
				tot -= r;
				qtd_1++;
			}
		}

		if (tot == 0)
		{
			printf("%lld\n", ans);
			return 0;
		}
	}

	printf("%lld\n", ans);
}
