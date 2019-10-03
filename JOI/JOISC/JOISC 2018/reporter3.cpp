// JOI Spring Camp 2018 - Worst Reporter 3
// Lúcio Cardoso

// Solution:

// 1. Let f(i) be the time it takes for i to move once. Notice that f(0) = 1 and f(1) = D_1.

// 2. We can observe that f(i) = ceil(D_i / f(i-1)) * f(i-1).

// 3. Now, we can binary search the first contestant that goes to a position >= L with time T
// and the last contestant that goes to a position <= R with time T.
// The amount of movements that contestant i makes with time T is floor(T/f(i)), and thus, the
// resulting position is f(i) * floor(T/f(i)) - i.

// Complexity: O(n log n)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n;

int d[maxn];
int tempo[maxn];

int busca1(int t, int pos)
{
	int ini = 0, fim = n, ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if ((t/tempo[mid])*tempo[mid] - mid >= pos) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	return ans;
}

int busca2(int t, int pos)
{
	int ini = 0, fim = n, ans = n+1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if ((t/tempo[mid])*tempo[mid] - mid <= pos) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);

	tempo[0] = 1, tempo[1] = d[1];
	for (int i = 2; i <= n; i++)
	{
		int x = d[i]/tempo[i-1];

		if (d[i]%tempo[i-1] != 0) x++;

		tempo[i] = x*tempo[i-1];
	}

	for (int i = 1; i <= q; i++)
	{
		int t, l, r;
		scanf("%d %d %d", &t, &l, &r);

		int R = busca2(t, r);
		int L = busca1(t, l);

		if (R > L) printf("0\n");
		else printf("%d\n", L-R+1);
	}
}
