// Codeforces 1333F - Kate and imperfection
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

bool mark[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	int d = n/2;

	vector<int> ans;

	for (int i = n; i > 1; i--)
	{
		int qtd = 0;
		for (int j = d; j <= n; j += d)
		{
			if (!mark[j])
			{
				qtd++;
				if (qtd != 1)
					mark[j] = true;
			}
		}

		if (qtd <= 1)
		{
			i++, d--;
			continue;
		}

		for (int j = 1; j < qtd; j++)
		{
			ans.push_back(d);
			i--;
		}

		i++, d--;
	}

	reverse(ans.begin(), ans.end());

	for (auto x: ans)
		printf("%d ", x);
	printf("\n");
}
