// BOI 2012 - Peaks
// Lúcio Cardoso

// Solution is the same as: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2012_solutions/peaks-sol.pdf

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e3+10;

int linha[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int coluna[] = {0, -1, 1, 0, -1, 1, 0, -1, 1};

int n, m;
int tab[maxn][maxn];

int peakId[maxn][maxn];
bool isPeak[maxn*maxn];

int ans[maxn*maxn];

int pai[maxn*maxn], peso[maxn*maxn], mx[maxn*maxn];
vector<int> peak[maxn*maxn];

bool on[maxn][maxn], mark[maxn*maxn];

bool comp(pii a, pii b)
{
	return (tab[a.first][a.second] > tab[b.first][b.second]);
}

bool comp2(pii a, pii b)
{
	if (a.first == b.first) return a.second > b.second;
	return a.first > b.first;
}

void dfs(int x, int y, int id)
{
	peakId[x][y] = id;

	for (int i = 0; i < 9; i++)
	{
		int a = x+linha[i], b = y+coluna[i];
		if (a < 1 || a > n || b < 1 || b > m) continue;

		if (tab[a][b] > tab[x][y]) isPeak[id] = false;
		if (peakId[a][b] || tab[a][b] != tab[x][y]) continue;

		dfs(a, b, id);
	}
}

int pos(int i, int j)
{
	return (i-1)*m + j;
}

void init(void)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			pai[pos(i, j)] = pos(i, j), peso[pos(i, j)] = 1;

			if (isPeak[peakId[i][j]])
			{
				mx[pos(i, j)] = tab[i][j];
				peak[pos(i, j)].push_back(peakId[i][j]);
			}
		}
	}
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Merge(int x, int y, int w)
{
	if (mx[x] == mx[y])
	{
		for (auto id: peak[y])
			peak[x].push_back(id);
	}
	else if (mx[x] > mx[y])
	{
		for (auto id: peak[y])
			ans[id] = max(ans[id], w);
	}
	else
	{
		for (auto id: peak[x])
			ans[id] = max(ans[id], w);

		swap(peak[x], peak[y]);
	}
}

void Join(int x, int y, int w)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];

	Merge(x, y, w);

	mx[x] = max(mx[x], mx[y]);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &tab[i][j]);

	int id = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (!peakId[i][j])
			{
				++id;
				isPeak[id] = true;

				dfs(i, j, id);
			}
		}
	}

	init();

	vector<pii> V;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			V.push_back({i, j});

	sort(V.begin(), V.end(), comp);

	for (auto pp: V)
	{
		int x = pp.first, y = pp.second;

		for (int i = 0; i < 9; i++)
		{
			int a = x+linha[i], b = y+coluna[i];
			if (a < 1 || a > n || b < 1 || b > m || !on[a][b]) continue;

			Join(pos(x, y), pos(a, b), tab[x][y]);
		}

		printf("\n");

		on[x][y] = true;
	}

	vector<pii> final;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!mark[peakId[i][j]] && isPeak[peakId[i][j]])
				mark[peakId[i][j]] = true, final.push_back({tab[i][j], ans[peakId[i][j]]});

	sort(final.begin(), final.end(), comp2);

	printf("%d\n", (int)final.size());
	for (auto pp: final)
		printf("%d %d\n", pp.first, pp.second);
}
