// COCI 2014-2015 - Studentsko
// Lúcio Cardoso

// Solution:

// 1. Find the group of every element in the array, that is, on which of the N/K blocks it will be (from smallest to largest).
// 2. For every number in the array, change its value to its respective group.
// 3. The answer will be N - (LIS of array).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;

int n;
int a[maxn], aux[maxn];

int lis(void)
{
	vector<int> v;

	for (int i = 1; i <= n; i++)
	{
		vector<int>::iterator it = upper_bound(v.begin(), v.end(), a[i]);

		if (it == v.end())
			v.push_back(a[i]);
		else
			*it = a[i];
	}

	return v.size();
}

int main(void)
{
	int k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		aux[i] = a[i];
	}

	sort(aux+1, aux+n+1);

	map<int, int> group;

	for (int i = 1; i <= n; i++)
		group[aux[i]] = (i-1)/k;

	for (int i = 1; i <= n; i++)
		a[i] = group[a[i]];

	printf("%d\n", n-lis());
}
