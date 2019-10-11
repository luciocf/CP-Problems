// infoarena - Casute
// Lúcio Cardoso

// Solution:

// 1. Compress heights. For each vertex, run a bfs and mark on a bitset
// the heights that this vertex reaches.

// 2. The answer for a pair of vertices is the vertex with height equal to the LSB
// of the intersection of bitsets from each of the vertices in said pair.

// Complexity: O(n^3/32)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;
const int mod = 666013;

int n, m;
int h[maxn];
int back[maxn];

vector<int> grafo[maxn];

bitset<maxn> reach[maxn];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[h[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		h[i] = mp[h[i]];
		back[h[i]] = i;
	}
}

void bfs(int s)
{
	queue<int> fila;
	fila.push(s);

	reach[s][h[s]] = 1;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (!reach[s][h[v]])
			{
				reach[s][h[v]] = 1;
				fila.push(v);
			}
		}
	}
}

int main(void)
{
	freopen("casute.in", "r", stdin);
	freopen("casute.out", "w", stdout);
	
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);

	compress();

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
	}

	for (int i = 1; i <= n; i++)
		bfs(i);

	int ans = 0, pot = 1;

	for (int i = n; i >= 1; i--)
	{
		for (int j = n; j > i; j--)
		{	
			int lsb = back[(reach[i]&reach[j])._Find_first()];

			ans += (lsb*pot)%mod;
			if (ans > mod) ans -= mod;

			pot = (pot*(n+1))%mod;
		}
	}

	printf("%d\n", ans);
}
