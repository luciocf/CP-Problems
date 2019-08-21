// infoarena - Arbore
// Lúcio Cardoso

// Solution:

// 1. Linearize the tree with a dfs tour and store in an array.

// 2. Divide the tour array in sqrt(N) blocks. For each block, mantain in an array S[] the sum of the values in updates that cover
// the entire block (that is, the values which were added to all elements in the block).

// 3. Use a bitset for each block that stores the values that exist inside it which were made by updates that didn't cover the entire block.
// To find an answer to a query of value K, iterate over all blocks and check if, in a certain block, the element K-S[] exists in its bitset.
// If so, one of the elements in the block is a solution.

// Overall complexity is O(m sqrt(n)). 

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxv = 1e6+10;
const int bucket = 320;

int n, m;

int st[maxn], en[maxn], vert[maxn], tt = -1;

int a[maxn];

int soma[maxn];

vector<int> grafo[maxn];

bitset<maxv> existe[bucket];

void dfs(int u, int p)
{
	st[u] = ++tt;
	vert[tt] = u;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	en[u] = tt;
}

int main(void)
{
	FILE *fin = fopen("arbore.in", "r");
	FILE *fout = fopen("arbore.out", "w");

	fscanf(fin, "%d %d", &n, &m);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0);

	for (int i = 0; i < n; i++)
		existe[i/bucket][0] = 1;

	for (int i = 1; i <= m; i++)
	{
		int op;
		fscanf(fin, "%d", &op);

		if (op == 1)
		{
			int u, v;
			fscanf(fin, "%d %d", &u, &v);

			int l = st[u], r = en[u];

			int p = l/bucket, k = r/bucket;

			if (p == k)
			{
				for (int i = l; i <= r; i++)
					existe[p][a[i]] = 0;

				for (int i = p*bucket; i < min(n, (p+1)*bucket); i++)
					if (i < l || i > r)
						existe[p][a[i]] = 1;

				for (int i = l; i <= r; i++)
				{
					a[i] += v;
					existe[p][a[i]] = 1;
				}
			}
			else
			{
				for (int i = p+1; i < k; i++)
					soma[i] += v;

				for (int i = l; i < min(n, (p+1)*bucket); i++)
					existe[p][a[i]] = 0;

				for (int i = k*bucket; i <= r; i++)
					existe[k][a[i]] = 0;

				for (int i = p*bucket; i < l; i++)
					existe[p][a[i]] = 1;

				for (int i = r+1; i < min(n, (k+1)*bucket); i++)
					existe[k][a[i]] = 1;

				for (int i = l; i < min(n, (p+1)*bucket); i++)
				{
					a[i] += v;
					existe[p][a[i]] = 1;
				}

				for (int i = k*bucket; i <= r; i++)
				{
					a[i] += v;
					existe[k][a[i]] = 1;
				}
			}
		}
		else
		{
			int v;
			fscanf(fin, "%d", &v);

			bool ok = 0;

			for (int i = 0; i <= (n-1)/bucket; i++)
			{
				if (ok) break;

				if (v >= soma[i] && existe[i][v-soma[i]])
				{
					ok = 1;

					for (int j = i*bucket; j < min(n, (i+1)*bucket); j++)
					{
						if (a[j]+soma[i] == v)
						{
							fprintf(fout, "%d\n", vert[j]);
							break;
						}
					}
				}
			}

			if (!ok)
				fprintf(fout, "-1\n");
		}
	}
}
