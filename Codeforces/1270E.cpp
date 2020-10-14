// Codeforces 1270E - Divide Points
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int x[maxn], y[maxn];

int md(int k)
{
	return abs(k)%2;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &x[i], &y[i]);
		x[i] += 1000000, y[i] += 1000000;
	}

	int qtd[2][2];

	while (true)
	{
		qtd[0][0] = qtd[0][1] = qtd[1][0] = qtd[1][1] = 0;

		for (int i = 1; i <= n; i++)
			qtd[md(x[i])][md(y[i])]++;

		if (max({qtd[0][0], qtd[0][1], qtd[1][0], qtd[1][1]}) != qtd[0][0]+qtd[0][1]+qtd[1][0]+qtd[1][1])
			break;

		for (int i = 1; i <= n; i++)
			x[i] /= 2, y[i] /= 2;
	}

	vector<int> ans;

	if ((qtd[0][0] + qtd[1][1]) && (qtd[0][1] + qtd[1][0]))
	{
		for (int i = 1; i <= n; i++)
			if (md(x[i]) == md(y[i]))
				ans.push_back(i);
	}
	else if (qtd[0][0] + qtd[1][1])
	{
		for (int i = 1; i <= n; i++)
			if (md(x[i]) && md(y[i]))
				ans.push_back(i);
	}
	else
	{
		for (int i = 1; i <= n; i++)
			if (md(x[i]) == 0 && md(y[i]))
				ans.push_back(i);
	}

	printf("%d\n", ans.size());
	for (auto i: ans)
		printf("%d ", i);
	printf("\n");
}
