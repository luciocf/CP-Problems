// POI 2004 - East-West
// Lúcio Cardoso

// NOTE: Due to the tight ML in this problem, my code only gets 84 points. However, the idea is correct.

// Solution idea is the same as: https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI04-East_West.cpp 

// The only difference is how I find the edge that separates the east and west vertices. To do that,
// I calculate the amount of east and west vertices in every subtree. For any edge (u, v) where
// u is the parent of v, the edge (u, v) will be desired edge if one of the two cases below apply:

//	- Every eastern vertex is in the subtree of v, and there are no west vertices in such subtree.
//	- Every western vertex is in the subtree of v, and there are no east vertices in such subtree.

// In the first case, u will be the critical node. In the latter, this vertex will be v.

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6;

int n, e, w, p;

int root=-1;

bool train[maxn];

pii pp;

vector<int> grafo[maxn];
vector<int> v_train, v_west;

void dfs(int u, int p)
{
	if (root != -1) return;
	int qtd_e = 0, qtd_w = 0;

	if (u < e) qtd_e = 1;
	if (u >= n-w) qtd_w = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);
		if (root != -1) return;

		if (pp.first == e && pp.second == 0)
		{
			root = u;
			return;
		}

		if (pp.second == w && pp.first == 0)
		{
			root = v;
			return;
		}

		qtd_e += pp.first, qtd_w += pp.second;
	}

	if (root != -1) return;
	pp = {qtd_e, qtd_w};
}

void calc_nivel(int u, int p, int nivel)
{
	if (train[u]) v_train.push_back(nivel);
	if (u >= n-w) v_west.push_back(nivel);

	for (auto v: grafo[u])
		if (v != p)
			calc_nivel(v, u, nivel+1);
}

int main(void)
{
	scanf("%d %d %d", &n, &e, &w);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		--u, --v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	scanf("%d", &p);

	for (int i = 0; i < p; i++)
	{
		int u;
		scanf("%d", &u);

		--u;

		train[u] = 1;
	}

	dfs(0, -1); calc_nivel(root, -1, 0);

	for (int i = 0; i < n; i++)
		grafo[i].clear();

	sort(v_train.begin(), v_train.end());
	sort(v_west.begin(), v_west.end());

	for (int i = 1; i < p; i++)
		if (v_train[i] <= v_train[i-1])
			v_train[i] = v_train[i-1]+1;

	int ans = 0;

	for (int i = 0; i < p; i++)
		ans = max(ans, v_train[i] + v_west[p-i-1]);

	v_train.clear(), v_west.clear();
	v_train.clear(), v_west.clear();

	printf("%d\n", ans);
}
