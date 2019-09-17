// TOKI Open 2018 - Tile Covering
// Lúcio Cardoso

// Solution:

// 1. Calculate tab[i][j] in O(M log N) -> the index of the last uncovered position that
// is covered if we use 2^j tiles starting at the index i of the array.

// 2. After that, we can answer the query using binary lifting.

#include <bits/stdc++.h>
#include "tile.h"

using namespace std;

const int maxn = 3e5+10;

int tab[maxn][31];

vector<int> a;

void init(int N, int K, int Q, int M, std::vector<int> A)
{
	a.resize(M);

	for (int i = 0; i < M; i++)
		a[i] = A[i];

	for (int i = 0; i < M; i++)
	{
		auto it = lower_bound(a.begin(), a.end(), a[i]+K-1);

		if (it == a.end()) tab[i][0] = M-1;
		else
		{
			it = upper_bound(a.begin(), a.end(), a[i]+K-1);

			if (it != a.end()) tab[i][0] = (int) (it-a.begin()-1);
			else tab[i][0] = M-1;
		}
	}

	for (int j = 1; j <= 30; j++)
		for (int i = 0; i < M; i++)
			tab[i][j] = (tab[i][j-1] == M-1 ? M-1 : tab[tab[i][j-1]+1][j-1]);
}

int getNumberOfSpecialTiles(int L, int R)
{
	auto it = lower_bound(a.begin(), a.end(), L);

	if (it == a.end() || *it > R) return 0;

	int l = (int) (it-a.begin());
	int r = (int) (upper_bound(a.begin(), a.end(), R)-a.begin()-1);

	int at = l, ans = 0;
	for (int i = 30; i >= 0; i--)
		if (tab[at][i] < r)
			at = tab[at][i]+1, ans += (1<<i);

	return ans+1;
}
