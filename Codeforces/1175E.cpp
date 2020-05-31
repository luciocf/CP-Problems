// Codeforces 1175E - Minimal Segment Cover
// Lúcio Cardoso

// Solution: Same as editorial, using binary lifting

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int tab[maxn][21];

int sai[maxn];

vector<int> entra[maxn];

void build(void)
{
	for (int j = 1; j <= 20; j++)
		for (int i = 0; i < maxn; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int get(int l, int r)
{
	int ans = 0;

	for (int i = 20; i >= 0; i--)
		if (tab[l][i] < r)
			l = tab[l][i], ans += (1<<i);

	if (tab[l][0] >= r) return ans+1;
	return -1;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		entra[l].push_back(r);
		sai[r]++;
	}

	multiset<int> st;

	for (int i = 0; i < maxn; i++)
	{
		for (auto r: entra[i])
			st.insert(-r);

		if (st.size())
			tab[i][0] = -*st.begin();
		else
			tab[i][0] = 0;

		for (int j = 1; j <= sai[i]; j++)
			st.erase(-i);
	}

	build();

	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		printf("%d\n", get(l, r));
	}
}
