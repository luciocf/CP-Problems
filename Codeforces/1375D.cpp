// CF 1375D - Replace by MEX
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e3+10;
 
int a[maxn];
bool mark[maxn];
 
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

		vector<int> V;

		while (true)
		{
			bool ok = true;

			for (int i = 1; i <= n; i++)
			{
				if (a[i] != i-1)
				{
					ok = false;
					break;
				}
			}

			if (ok) break;

			for (int i = 0; i <= n; i++)
				mark[i] = false;
			for (int i = 1; i <= n; i++)
				mark[a[i]] = true;

			int mex;
			for (int i = 0; i <= n; i++)
			{
				if (!mark[i])
				{
					mex = i;
					break;
				}
			}

			if (mex == n)
			{
				for (int i = 1; i <= n; i++)
				{
					if (a[i] != i-1)
					{
						V.push_back(i);
						swap(a[i], mex);
						break;
					}
				}
			}
			else
			{
				V.push_back(mex+1);
				swap(a[mex+1], mex);
			}
		}
 
		printf("%d\n", V.size());
		for (auto p: V)
			printf("%d ", p);
		printf("\n");
	}
}
