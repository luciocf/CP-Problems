// Infoarena - Engineer
// Lúcio Cardoso

/* Solution:

Use parallel binary search on the value.

After processing all queries with middle in a value V, add 1 to every position (i, j) such that a[i][j] = V
in a BIT (not a 2d BIT, just a BIT for every row).

Let the binary search mid value of a query be V. Doing what was mentioned above, we can decide how to
update the binary search interval to a query: just iterate through the rows of the submatrix and calculate
the sum in the interval [y1, y2] for each one (using the BIT). If this sum is < k, then there are less than
k values strictly smaller than V, so the BS interval should become [V+1, r]. Otherwise, the interval should become
[l, V-1].

Complexity: O(M*(N+Q) * log (N*M)) (note: TL is very tight here)
*/

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1110;
const int maxv = 2e6+10;

int n, m, q;
int a[maxn][maxn];

vector<pair<int, pii>> V;

struct Query
{
	int x1, y1, x2, y2, k;
} query[maxn];

struct FenwickTree
{
	int bit[maxn][maxn];

	void upd(int ind, int x, int v)
	{
		for (; x <= m; x += (x&-x))
			bit[ind][x] += v;
	}

	int soma(int ind, int x)
	{
		int ans = 0;

		for (; x > 0; x -= (x&-x))
			ans += bit[ind][x];

		return ans;
	}

	int get(int ind, int l, int r)
	{
		return soma(ind, r)-soma(ind, l-1);
	}
} BIT;

int ans[maxn];

int ini[maxn], fim[maxn];

void solve(void)
{
	bool flag = 1;

	for (int i = 1; i <= q; i++)
		ini[i] = 0, fim[i] = n*m-1;

	while (flag)
	{
		memset(BIT.bit, 0, sizeof BIT.bit);
		flag = 0;

		vector<pii> query_ind;

		for (int i = 1; i <= q; i++)
		{
			if (ini[i] <= fim[i])
			{
				flag = 1;

				int mid = (ini[i]+fim[i])/2;

				query_ind.push_back({mid, i});
			}
		}

		if (query_ind.size() == 0) continue;

		sort(query_ind.begin(), query_ind.end());

		int ptr = 0;

		while (ptr < V.size() && V[ptr].ff < V[query_ind[0].ff].ff)
		{
			BIT.upd(V[ptr].ss.ff, V[ptr].ss.ss, 1);
			ptr++;
		}

		for (int it = 0; it < query_ind.size(); it++)
		{
			pii pp = query_ind[it];

			int v = pp.ff, q_ind = pp.ss;
			auto qq = query[q_ind];

			int x1 = qq.x1, x2 = qq.x2, y1 = qq.y1, y2 = qq.y2, k = qq.k;

			int soma = 0;
			for (int i = x1; i <= x2; i++)
				soma += BIT.get(i, y1, y2);

			if (soma < k) ans[q_ind] = v, ini[q_ind] = v+1;
			else fim[q_ind] = v-1;

			if (it == (int)query_ind.size()-1) continue;

			while (ptr < V.size() && V[ptr].ff < V[query_ind[it+1].ff].ff)
			{
				BIT.upd(V[ptr].ss.ff, V[ptr].ss.ss, 1);
				ptr++;
			}
		}
	}
}

int main(void)
{
	freopen("engineer.in", "r", stdin); freopen("engineer.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			V.push_back({a[i][j], {i, j}});

	sort(V.begin(), V.end());

	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
		scanf("%d %d %d %d %d", &query[i].x1, &query[i].y1, &query[i].x2, &query[i].y2, &query[i].k);

	solve();

	for (int i = 1; i <= q; i++)
		printf("%d\n", V[ans[i]].ff);
}
