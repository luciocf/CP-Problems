// Codeforces 819E - Mister B and Flight to the Moon
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;

int main(void)
{
	int n;
	scanf("%d", &n);

	vector<vector<int>> ciclos;

	if (n%2 == 0)
	{
		ciclos.push_back({1, 3, 4});
		ciclos.push_back({2, 3, 4});
		ciclos.push_back({1, 2, 4});
		ciclos.push_back({1, 2, 3});

		for (int i = 6; i <= n; i += 2)
		{
			for (int j = 2; j <= i-4; j += 2)
			{
				ciclos.push_back({i-1, j-1, i, j});
				ciclos.push_back({i-1, j-1, i, j});
			}

			ciclos.push_back({i-1, i-3, i, i-2});
			ciclos.push_back({i-1, i-3, i});
			ciclos.push_back({i-1, i, i-2});
		}
	}
	else
	{
		ciclos.push_back({1, 2, 3});
		ciclos.push_back({1, 2, 3});

		for (int i = 5; i <= n; i += 2)
		{
			for (int j = 2; j <= i-3; j += 2)
			{
				ciclos.push_back({i-1, j-1, i, j});
				ciclos.push_back({i-1, j-1, i, j});
			}

			ciclos.push_back({i-1, i-2, i});
			ciclos.push_back({i-1, i-2, i});
		}
	}

	printf("%d\n", (int)ciclos.size());
	for (auto c: ciclos)
	{
		printf("%d", (int)c.size());
		for (auto v: c)
			printf(" %d", v);
		printf("\n");
	}
}
