// POI 2012 - Squarks
// Lúcio Cardoso

// Solution is the same as in: https://github.com/timpostuvan/competitive-programming/blob/master/Olympiad/POI/Squarks19.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;

int a[maxn];
int b[maxn*maxn];

set<vector<int>> ans;

int main(void)
{
	int n;
	scanf("%d", &n);

	int m = (n*(n-1))/2;

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	sort(b+1, b+m+1);

	for (int t = 3; t <= n; t++)
	{
		int x = b[1]+b[2] - b[t];
		if (x%2 || x <= 0) continue;

		multiset<int> st;

		for (int i = 1; i <= m; i++)
			st.insert(b[i]);

		int ind = 1;
		a[1] = x/2;

		bool ok = true;
		
		while (ok && st.size())
		{
			a[++ind] = *st.begin()-a[1];

			for (int i = 1; i < ind; i++)
			{
				if (st.find(a[i]+a[ind]) == st.end())
				{
					ok = false;
					break;
				}
				else st.erase(st.find(a[i]+a[ind]));
			}
		}

		if (ok)
		{
			vector<int> V;
			for (int i = 1; i <= n; i++)
				V.push_back(a[i]);

			ans.insert(V);
		}
	}

	printf("%d\n", (int)ans.size());
	for (auto it: ans)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d", it[j]);
			if (j != n-1) printf(" ");
			else printf("\n");
		}
	}
}
