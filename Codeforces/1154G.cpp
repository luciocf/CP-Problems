// Codeforces 1154G - Minimum Possible LCM
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e7+10;
const ll inf = 1e18+10;

int a[maxn];

pair<int, int> pos[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (!pos[a[i]].first) pos[a[i]].first = i;
		else pos[a[i]].second = i;
	}

	ll ans = inf;
	int ind1 = 0, ind2 = 0;

	for (int i = 1; i <= 10000000; i++)
	{
		int menor1 = -1, menor2 = -1;

		for (int j = i; j <= 10000000; j += i)
		{
			if (pos[j].first)
			{
				if (menor1 == -1)
				{
					menor1 = pos[j].first;

					if (pos[j].second)
					{
						menor2 = pos[j].second;
						break;
					}
				}
				else
				{
					menor2 = pos[j].first;
					break;
				}
			}
		}

		if (menor2 != -1 && 1ll*a[menor1]*a[menor2]/i < ans)
		{
			ans = 1ll*a[menor1]*a[menor2]/i;
			ind1 = menor1, ind2 = menor2;
		}
	}

	if (ind1 > ind2) swap(ind1, ind2);
	
	printf("%d %d\n", ind1, ind2);
}
