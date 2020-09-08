// CEERC 2013 - I - Crane
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e4+10;

int a[maxn];

void change(int l_1, int r_1, int l_2, int r_2)
{
	assert(r_1-l_1 == r_2-l_2);

	for (int i = l_1, j = l_2; i <= r_1; i++, j++)
		swap(a[i], a[j]);
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		vector<pii> ans;

		for (int i = 1; i <= n; i++)
		{
			int pos;
			for (int j = 1; j <= n; j++)
			{
				if (a[j] == i)
				{
					pos = j;
					break;
				}
			}

			if (pos == i) continue;

			if (2*(pos-i) <= n-i+1)
			{
				ans.push_back({i, 2*pos-i-1});
				change(i, pos-1, pos, 2*pos-i-1);
			}
			else
			{
				int mid = (pos+i)/2;

				if ((pos+i)%2 == 0)
				{
					ans.push_back({i+1, pos});
					change(i+1, mid, mid+1, pos);
				}
				else
				{
					ans.push_back({i, pos});
					change(i, mid, mid+1, pos);
				}

				if (mid != i)
				{
					ans.push_back({i, 2*mid-i-1});
					change(i, mid-1, mid, 2*mid-i-1);
				}
			}
		}

		printf("%d\n", ans.size());
		for (auto pp: ans)
			printf("%d %d\n", pp.first, pp.second);
	}
}
