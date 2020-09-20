// USACO 2016/2017 - Robotic Cow Herd
// Lúcio Cardoso

// TODO Solution

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n, k;
vector<int> a[maxn];

int delta[maxn];

ll get(void)
{
	ll soma = 0, ans = 0;
	vector<int> good;

	for (int i = 1; i <= n; i++)
	{
		sort(a[i].begin(), a[i].end());

		soma += 1ll*a[i][0];

		if (a[i].size() > 1)
		{
			good.push_back(i);
			delta[i] = a[i][0]-a[i][1];
		}
	}

	ans += soma;

	if (good.size() == 0) return ans;

	sort(good.begin(), good.end(), [&] (int a, int b) {return delta[a] > delta[b];});

	priority_queue<pair<ll, pii>, vector<pair<ll, pii>>, greater<pair<ll, pii>>> fila;
	fila.push({soma - delta[good[0]], {0, 1}});

	int tot = 1;

	while (tot < k)
	{
		auto pp = fila.top(); fila.pop();

		ll s = pp.ff;
		int i = pp.ss.ff, j = pp.ss.ss;

		ans += s;
		tot++;

		if (j < (int)a[good[i]].size()-1)
			fila.push({s - 1ll*a[good[i]][j] + 1ll*a[good[i]][j+1], {i, j+1}});

		if (i < (int)good.size()-1)
			fila.push({s - 1ll*delta[good[i+1]], {i+1, 1}});

		if (i < (int)good.size()-1 && j == 1)
			fila.push({s + 1ll*delta[good[i]] - 1ll*delta[good[i+1]], {i+1, 1}});
	}

	return ans;
}

int main(void)
{
	freopen("roboherd.in", "r", stdin); freopen("roboherd.out", "w", stdout);

	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);

		while (m--)
		{
			int x;
			scanf("%d", &x);

			a[i].push_back(x);
		}
	}

	printf("%lld\n", get());
}
