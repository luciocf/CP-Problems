// Codeforces 487C - Prefix Product Sequence
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

bool prime(int x)
{
	for (int i = 2; i*i <= x; i++)
		if (x%i == 0)
			return 0;

	return 1;
}

int pot(int a, int b)
{
	int ans = 1;
	int p = b+2;

	for (; b; b /= 2, a = (1ll*a*a)%p)
		if (b&1)
			ans = (1ll*ans*a)%p;

	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	if (n == 4)
	{
		printf("YES\n1\n3\n2\n4\n");
		return 0;
	}

	if (!prime(n))
	{
		printf("NO\n");
		return 0;
	}

	printf("YES\n1\n");

	for (int i = 2; i <= n; i++)
	{
		int x = (1ll*i*pot(i-1, n-2))%n;
		if (x == 0) x = n;

		printf("%d\n", x);
	}
}
