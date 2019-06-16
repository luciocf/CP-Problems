// CEOI 2003 - Towers of Hanoi
// Lúcio Cardoso

// Solution is the same as this one: http://ceoi.inf.elte.hu/probarch/03/hanoi-solution.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e6;

int n, s1, s2, s3;

int pos[maxn];

int pot[maxn];

int diff(int a, int b)
{
	if (a != 1 && b != 1) return 1;
	if (a != 2 && b != 2) return 2;
	return 3;
}

int solve(int x, int to)
{
	if (x <= 0) return 0;
	if (pos[x] == to) return solve(x-1, to);

	return (pot[x-1]+solve(x-1, diff(pos[x], to)))%mod;
}

int main(void)
{
	scanf("%d %d %d %d", &n, &s1, &s2, &s3);

	for (int i = 1; i <= s1; i++)
	{
		int x;
		scanf("%d", &x);

		pos[x] = 1;
	}

	for (int i = 1; i <= s2; i++)
	{
		int x;
		scanf("%d", &x);

		pos[x] = 2;
	}

	for (int i = 1; i <= s3; i++)
	{
		int x;
		scanf("%d", &x);

		pos[x] = 3;
	}

	pot[0] = 1;
	for (int i = 1; i <= n; i++)
		pot[i] = (2ll*pot[i-1])%mod;

	printf("%d\n%d\n", pos[n], solve(n, pos[n]));
}
