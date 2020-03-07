// Codeforces 1305E - Kuroni and the Score Distribution
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	vector<int> ans;

	int last;

	for (last = 1; last <= n; last++)
	{
		if (m >= (last-1)/2)
		{
			m -= (last-1)/2;
			ans.push_back(last);
		}
		else break;
	}

	--last;

	if (last == n && m != 0)
	{
		printf("-1\n");
		return 0;
	}

	if (m > 0)
	{
		for (int i = 1; i <= last; i++)
		{
			if (m == (last-i+1)/2)
			{
				ans.push_back(i+last);
				m -= (last-i+1)/2;
				break;
			}
		}
	}

	if (m != 0)
	{
		printf("-1\n");
		return 0;
	}

	int aux = 1000000000 - n*10000;

	for (int i = ans.size()+1; i <= n; i++)
	{
		ans.push_back(aux);
		aux += 10000;
	}

	for (auto x: ans)
		printf("%d ", x);
	printf("\n");
}
