// BOI 2020 - Graph
// Lúcio Cardoso

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n, m;
long double a[maxn];

vector<pii> grafo[maxn];

int sign[maxn], cte[maxn];
vector<int> comp;

bool mark[maxn];

long double f(long double x)
{
	long double ans = 0;

	for (auto u: comp)
		ans += abs(1.00*sign[u]*x + 1.00*cte[u]);

	return ans;
}

long double search(long double l, long double r)
{
  	for (int i = 1; i <= 1000; i++)
    {
        long double mid1 = l + (r - l)/3.00;
        long double mid2 = r - (r - l)/3.00;

        long double f1 = f(mid1);
        long double f2 = f(mid2);

        if (f1 < f2) r = mid2;
        else l = mid1;
    }

    return l;
}

void dfs(int u)
{
	comp.push_back(u);

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;
		if (sign[v]) continue;

		sign[v] = (sign[u] == 1 ? -1 : 1);
		cte[v] = w-cte[u];

		dfs(v);
	}
}

void color(int u)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;
		if (mark[v]) continue;

		a[v] = 1.00*w-a[u];
		color(v);
	}
}

bool certo(int u, long double x)
{
	for (auto x: comp)
		mark[x] = 0;

	a[u] = x;
	color(u);

	for (auto x: comp)
		for (auto y: grafo[x])
			if (fabs(a[x] + a[y.ff] - (long double)y.ss) > 1e-6)
				return false;

	return true;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);
	cout.precision(10);
    cout << fixed;

	cin >> n >> m;

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}
	
	for (int i = 1; i <= n; i++)
	{
		if (sign[i] == 0)
		{
			sign[i] = 1;
			comp.clear();
			dfs(i);

			long double x;
			bool fixo = 0;

			for (auto u: comp)
			{
				for (auto pp: grafo[u])
				{
					int v = pp.first, w = pp.second;

					if (sign[v] == sign[u])
					{
						x = 1.00*sign[u]*(w-cte[u]-cte[v])/2.00;
						fixo = 1;
						break;
					}
				}
			}

			if (!fixo)
				x = search(-1e9, 1e9);

			if (!certo(i, x))
			{
				printf("NO\n");
				return 0;
			}
		}
	}

	cout << "YES\n";
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << "\n";
}
