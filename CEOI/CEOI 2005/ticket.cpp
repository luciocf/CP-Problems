// CEOI 2005 - Ticket Office
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2005/solticket.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, l, m;

int ind[maxn];

bool mark[maxn];

int main(void)
{
	scanf("%d %d %d", &n, &l, &m);

	for (int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);

		mark[x] = 1;

		ind[x] = i;
	}

	vector<int> V;

	int last = n+1;

	for (int i = n; i >= 1; i--)
	{
		if (!mark[i]) continue;

		if (last-i >= l)
		{
			last = i;
			V.push_back(i);
		}
	}

	reverse(V.begin(), V.end());

	for (int i = 0; i < V.size(); i++)
	{
		int last = (i == 0 ? 0 : V[i-1]+l-1);
		int qtd = (V[i]-last-1)/l;

		int outro = -1;

		for (int j = V[i]-1; j > last && (j-last-1)/l == qtd; j--)
			if (mark[j])
				outro = j;

		if (outro != -1)
			V[i] = outro;
	}

	memset(mark, 0, sizeof mark);

	vector<pair<int, int>> ans;
	int resp = 2*(int)V.size();

	for (auto i: V)
	{
		ans.push_back({i, ind[i]});
		mark[ind[i]] = 1;
	}

	vector<int> P;
	for (int i = 1; i <= m; i++)
		if (!mark[i])
			P.push_back(i);

	for (int i = 0; i < V.size(); i++)
	{
		int qtd = 0;
		int ant = (i == 0 ? 1 : V[i-1]+l);

		if (i == 0 && V[i] == 1) ant = n+1;

		for (int j = ant; j < V[i]; j++)
		{
			qtd++;

			if (qtd%l == 0 && P.size())
			{
				ans.push_back({j-l+1, P.back()});
				P.pop_back();
				resp++;
			}
		}
	}

	int qtd = 0;
	for (int j = V.back()+l; j <= n; j++)
	{
		qtd++;

		if (qtd%l == 0 && P.size())
		{
			ans.push_back({j-l+1, P.back()});
			P.pop_back();
			resp++;
		}
	}

	sort(ans.begin(), ans.end());

	printf("%d\n%d\n", resp, (int)ans.size());
	for (auto pp: ans)
		printf("%d %d\n", pp.second, pp.first);
}
