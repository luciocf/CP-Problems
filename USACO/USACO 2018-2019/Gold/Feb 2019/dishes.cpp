// USACO Gold Feb 2019 - Dishwashing
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], pos[maxn];
stack<int> stk[maxn];

int main(void)
{
	FILE *fin = fopen("dishes.in", "r");
	FILE *fout = fopen("dishes.out", "w");

	int n;
	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	set<int> S;
	vector<int> at;

	int l = 1, r = 0;

	for (int i = 1; i <= n; i++)
	{
		if (at.size() > 0 && a[i] < at.back())
		{
			fprintf(fout, "%d\n", i-1);
			return 0;
		}

		set<int>::iterator it = S.upper_bound(a[i]);

		if (it == S.end())
		{
			stk[++r].push(a[i]);
			S.insert(a[i]);

			pos[a[i]] = r;
		}
		else
		{
			int p = pos[*it];
			pos[a[i]] = p;

			if (stk[p].top() < a[i])
			{
				for (int j = l; j <= p; j++)
				{
					while (stk[j].size() > 0 && stk[j].top() < a[i])
					{
						at.push_back(stk[j].top());

						if (stk[j].size() == 1)
							S.erase(stk[j].top());

						stk[j].pop();
					}
				}
			}

			l = p;

			stk[pos[*it]].push(a[i]);
		}
	}

	fprintf(fout, "%d\n", n);
}
