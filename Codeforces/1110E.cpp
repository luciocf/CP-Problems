// Codeforces 1110E - Magic Stones
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], b[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);


	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);

	if (a[1] != b[1])
	{
		printf("No\n");
		return 0;
	}

	map<int, int> mp1, mp2;

	for (int i = 2; i <= n; i++)
	{
		mp1[a[i]-a[i-1]]++;

		mp2[b[i]-b[i-1]]++;
	}

	for (int i = 2; i <= n; i++)
	{
		if (mp1[a[i]-a[i-1]] != mp2[a[i]-a[i-1]])
		{
			printf("No\n");
			return 0;
		}
	}

	printf("Yes\n");
}
