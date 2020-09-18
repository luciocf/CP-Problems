// POI 2017 - Shipping Containers
// Lúcio Cardoso

/* Solution:

Define the array qtd[x][y] -> amount of operations done previously with d-value = x and a%d = y.

Iterate through every index i from 0 to n-1. Suppose there's an operation {a, d, l} in i (i.e a = i).

	* If d >= sqrt(n), just iterate through a, a + d, ..., a + (l-1)*d, adding
	one to the answer in these indices.

	* If d < sqrt(n), then add 1 to qtd[d][a%d] and add the pair {d, a%d} in a vector in position a + (l-1)*d to
	subtract qtd[d][a%d] by one in such position.

To get the answer for i for operations with d < sqrt(n), add qtd[b][i%b] to ans[i] for every b < sqrt(n).

After processing position i, subtract 1 from qtd[x][y] for every pair {x, y} in the vector of position i.

Complexity: O(n sqrt n)
*/

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxb = 320;

vector<pii> event[maxn];

int ans[maxn];
int qtd[maxb][maxb];

vector<pii> sub[maxn];

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= q; i++)
	{
		int a, d, l;
		scanf("%d %d %d", &a, &l, &d);
		--a;

		event[a].push_back({d, l});
	}

	for (int i = 0; i < n; i++)
	{
		for (auto pp: event[i])
		{
			int d = pp.ff, l = pp.ss;

			if (d >= maxb)
			{
				for (int j = i; j <= i+(l-1)*d; j += d)
					ans[j]++;
			}
			else
			{
				qtd[d][i%d]++;
				sub[i+(l-1)*d].push_back({d, i%d});
			}
		}

		for (int j = 1; j < maxb; j++)
			ans[i] += qtd[j][i%j];

		for (auto pp: sub[i])
			qtd[pp.ff][pp.ss]--;
	}

	for (int i = 0; i < n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
