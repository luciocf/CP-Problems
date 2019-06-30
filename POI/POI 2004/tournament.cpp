// POI 2004 - The Tournament
// Lúcio Cardoso

// Solution:

// Notations: Let V be the set of all players, W the set of all winners, and L the set of all losers.

// Lemma 1: Every player in W wins from every player in L.

// Proof: Suppose there is a pair (u, v) such that u belongs to W, v belong to L and u doesn't win from v. Then, take any configuration C
// of matches such that u wins. Remove the match that v loses from C and add a match that v wins from u as a last match. Then, in this scenario,
// v wins the tournament, which is an absurd.

// Lemma 1 suggests the following algorithm to find all winners:

// (Algorithm 1)
// 1. Let W' be a subset of W. At first, insert any winner S into W'.
// 2. While there is a player v such that v doesn't lose from every player in W', insert v into W'.

// Lemma 2: W' = W.

// Proof: Let's first prove that every player in W' wins. Let v the player to be added in W' in step 2. If v = S, by definition, v wins.
// Otherwise, let u be any player in W' such that v doesn't lose from u. Since u is a winner, take any configuration C
// of matches such that u wins. Remove the match that v loses from C and add a match that v wins from u as a last match. Then, it is proven
// that v wins and inductively, every player in W' wins. Now, it's simple to notice that every player in V / W' loses, since due to step 2
// of our algorithm, every player in W' wins from every player in V.

// To find an initial player S that wins, apply the following algorithm:

// 1. Let x = 1. Mark x as visited
// 2. While there is any player y not yet visited that wins from x, let x := y and mark x as visited. Otherwise, x is a winner.

// Then, all that remains is applying the Algorithm 1. To do that, maintain a set of pairs (a, b) where a is the amount
// of winning players in W' that win from b. At any moment, let P = (a, b) be the pair with minimal value a. If a is smaller than the size of W', 
// we insert v = b in W' and remove P from the set and update the pairs whose value b lose from v. Otherwise, we finish the algorithm.

// Overall complexity is O(m log n).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> pii;

int qtd[maxn];

bool mark[maxn];

vector<int> grafo[maxn], grafo_t[maxn];

set<pii> st;

int find_win(void)
{
	int at = 1;

	while (true)
	{
		mark[at] = true;

		bool find = 0;
		for (auto v: grafo_t[at])
		{
			if (!mark[v])
			{
				at = v, find = true;
				break;
			}
		}

		if (!find) break;
	}

	return at;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);

		for (int j = 1; j <= k; j++)
		{
			int v;
			scanf("%d", &v);

			grafo[i].push_back(v); grafo_t[v].push_back(i);
		}
	}

	int S = find_win();

	memset(mark, 0, sizeof mark);

	mark[S] = true;

	for (int i = 1; i <= n; i++)
		if (i != S)
			st.insert({0, i});

	for (auto v: grafo[S])
	{
		if (!mark[v])
		{
			st.erase({qtd[v], v});
			++qtd[v];
			st.insert({qtd[v], v});
		}
	}

	int tot_win = 1;
	vector<int> ans;

	ans.push_back(S);

	while (true)
	{
		if (tot_win == n) break;

		pii pp = *(st.begin());
		if (pp.first == tot_win) break;

		int u = pp.second;
		st.erase(pp);

		for (auto v: grafo[u])
		{
			if (!mark[v])
			{
				st.erase({qtd[v], v});
				++qtd[v];
				st.insert({qtd[v], v});
			}
		}

		++tot_win, mark[u] = true;
		ans.push_back(u);
	}

	sort(ans.begin(), ans.end());

	printf("%d", (int)ans.size());
	for (auto v: ans)
		printf(" %d", v);
	printf("\n");
}
