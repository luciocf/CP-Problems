// Singapore NOI 2017 - Best Place
// Lúcio Cardoso

// Solution:

// 1. The optimal X value can be one of the points' X value. Same goes for the optimal Y.

// 2. By doing some simple algebra, we can notice that the optimal X is actually the median
// of the points' X values. (similar for Y).

// Complexity: O(n)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

int n;
int x[maxn], y[maxn];

ll soma(int X, int Y)
{
	ll soma = 0;
	for (int i = 1; i <= n; i++)
	{
		soma += 1ll*abs(X-x[i]);
		soma += 1ll*abs(Y-y[i]);
	}

	return soma;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &x[i], &y[i]);

	sort(x+1, x+n+1); sort(y+1, y+n+1);

	int mid = (n-1)/2;

	int X = x[mid], Y = y[mid];

	ll ans = soma(X, Y);

	mid++;

	X = x[mid], Y = y[mid];

	if (soma(X, Y) < ans) printf("%d %d\n", X, Y);
	else
	{
		mid--;
		printf("%d %d\n", x[mid], y[mid]);
	}
}
