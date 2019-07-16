// IOI 2004 - Farmer
// Lúcio Cardoso

// Solution:

// 1. Check if it's possible to get sum Q with a simple knapsack on the fields.
// In case it's impossible, if the sum of field values is >= Q, we can get Q-1.

// 2. Otherwise, if we use a subset of fields and a subset of strips, our answer will be
// min(sum_of_fields + sum_of_strips, Q) - s, where s is the amount of strips used. Thus, it's always
// optimal to use whole fields and use all of them, because we can make sum_of_fields + sum_of_strips
// closer to Q without using any strip.

// 3. Similarly, we should always use strips in decreasing order of value (i.e choose the largest strip first,
// then the second largest, etc.), until the sum of fields and strips is >= Q.

// Complexity: O(m*Q + k log k)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 150010;

int valA[maxn], valB[maxn];
int dp[maxn];

bool comp(int a, int b) {return a > b;}

int main(void)
{
	int n, a, b;
	scanf("%d %d %d", &n, &a, &b);

	int soma = 0;

	for (int i = 1; i <= a; i++)
	{
		scanf("%d", &valA[i]);
		soma += valA[i];
	}

	for (int i = 1; i <= b; i++)
		scanf("%d", &valB[i]);

	for (int i = 1; i <= a; i++)
		for (int j = n; j >= valA[i]; j--)
			dp[j] = max(dp[j], dp[j-valA[i]]+valA[i]);

	if (dp[n] == n)
	{
		printf("%d\n", n);
		return 0;
	}

	if (soma >= n)
	{
		printf("%d\n", n-1);
		return 0;
	}

	sort(valB+1, valB+b+1, comp);

	for (int i = 1; i <= b; i++)
	{
		soma += valB[i];

		if (soma >= n)
		{
			printf("%d\n", n-i);
			return 0;
		}
	}
}
