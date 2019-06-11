// IOI 2009 - Regions
// Lúcio Cardoso

// Solution is the same as the "Precomputing Queries" solution presented here: http://www.ioi2009.org/GetResource?id=1969

// Essentialy, divide the regions in heavy and light ones.
// A region is heavy if it has > sqrt(N) vertices.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+5;
const int maxr = 25010;
const int block = 500;

typedef long long ll;

int n, R, q;
int region[maxn];

int st[maxn], en[maxn], tt;

int pre1[block][block], pre2[maxr][block];

vector<int> grafo[maxn], pos[maxr], V[maxr];

map<int, int> mp;

int dfs(int u, int p, int r)
{
	int qtd = (region[u] == r ? 1 : 0);

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		qtd += dfs(v, u, r);
	}

	if (V[region[u]].size() > block)
		pre1[mp[region[u]]][mp[r]] += 1ll*qtd;

	return qtd;
}

void dfs2(int u, int p, int r, int qtd)
{
	if (region[u] == r)
		++qtd;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pre2[region[v]][mp[r]] += 1ll*qtd;
		dfs2(v, u, r, qtd);
	}
}

void dfs3(int u, int p)
{
	st[u] = ++tt;
	pos[region[u]].push_back(tt);

	for (auto v: grafo[u])
		if (v != p)
			dfs3(v, u);

	en[u] = tt;
}

int main(void)
{
	cin >> n >> R >> q;

	cin >> region[1];
	for (int i = 2; i <= n; i++)
	{
		int p;
		cin >> p >> region[i];

		grafo[i].push_back(p); grafo[p].push_back(i);
	}

	for (int i = 1; i <= n; i++)
		V[region[i]].push_back(i);

	int aux = 0;
	for (int i = 1; i <= R; i++)
		if (V[i].size() > block)
			mp[i] = ++aux;

	for (int i = 1; i <= R; i++)
	{
		if (V[i].size() > block)
		{
			dfs(1, 0, i);
			dfs2(1, 0, i, 0);
		}
	}

	dfs3(1, 0);

	for (int i = 1; i <= q; i++)
	{
		int r1, r2;
		cin >> r1 >> r2;

		if (V[r1].size() > block && V[r2].size() > block)
		{
			cout << pre1[mp[r1]][mp[r2]] << endl;
		}
		else if (V[r1].size() > block && V[r2].size() <= block)
		{
			cout << pre2[r2][mp[r1]] << endl;
		}
		else
		{
			int ans = 0;

			for (auto ind: V[r1])
			{
				int l = st[ind], r = en[ind];

				vector<int>::iterator it1 = lower_bound(pos[r2].begin(), pos[r2].end(), l);
				vector<int>::iterator it2 = upper_bound(pos[r2].begin(), pos[r2].end(), r);

				if (it1 == pos[r2].end()) continue;
				if (it2 == pos[r2].begin()) continue;

				--it2;

				int pos1 = (int)(it1-pos[r2].begin()), pos2 = (int)(it2-pos[r2].begin());

				if (pos[r2][pos1] > r || pos[r2][pos2] < l) continue;

				ans += (pos2-pos1+1);
			}

			cout << ans << endl;
		}
	}
}
