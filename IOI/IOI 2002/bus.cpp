// IOI 2002 - Bus Terminals
// Lúcio Cardoso

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 510;

pii pt[maxn], aux[maxn];

int mx1[maxn], mx2[maxn];

pii h1;

int dist(pii a, pii b)
{
	return abs(a.x-b.x) + abs(a.y-b.y);
}

bool comp(pii a, pii b)
{
	return dist(a, h1) < dist(b, h1);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &pt[i].x, &pt[i].y);
		aux[i] = pt[i];
	}

	int ans = 1e9;

	for (int i = 1; i <= n; i++)
	{
		h1 = aux[i];
		sort(pt+1, pt+n+1, comp);

		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;
			pii h2 = aux[j];

			mx1[n] = n, mx2[n] = 0;

			for (int l = n-1; l >= 1; l--)
			{
				mx1[l] = mx1[l+1], mx2[l] = mx2[l+1];

				if (dist(pt[l], h2) > dist(pt[mx1[l]], h2)) mx2[l] = mx1[l], mx1[l] = l;
				else if (mx2[l] == 0 || dist(pt[l], h2) > dist(pt[mx2[l]], h2)) mx2[l] = l; 
			}

			if (mx2[2] == 0) ans = min(ans, dist(h1, h2)+dist(pt[mx1[2]], h2));
			else ans = min(ans, max(dist(h1, h2)+dist(pt[mx1[2]], h2), dist(pt[mx1[2]], h2)+dist(pt[mx2[2]], h2)));

			for (int l = n-1; l > 1; l--)
			{
				if (mx2[l+1] == 0)
				{
					ans = min(ans, max(dist(pt[l], h1)+dist(pt[mx1[l+1]], h1), dist(pt[mx1[l+1]], h1)+dist(h1, h2)));
				}
				else
				{
					pii A1 = pt[mx1[l+1]], A2 = pt[l];
					pii B1 = pt[mx2[l+1]];

					if (dist(A1, h1) >= dist(B1, h2))
						ans = min(ans, max(dist(A1, h1)+dist(A2, h1), dist(A1, h1)+dist(h1, h2)+dist(B1, h2)));
				}

				if (mx1[l+1] == l+1 && l+2 > n) continue;

				if (mx1[l+1] == l+1)
				{
					pii A1 = pt[l+2], A2 = pt[l];
					pii B1 = pt[mx1[l+1]];

					if (dist(A1, h1) >= dist(B1, h2))
						ans = min(ans, max(dist(A1, h1)+dist(A2, h1), dist(A1, h1)+dist(h1, h2)+dist(B1, h2)));
				}
				else
				{
					pii A1 = pt[l+1], A2 = pt[l];
					pii B1 = pt[mx1[l+1]];

					if (dist(A1, h1) >= dist(B1, h2))
						ans = min(ans, max(dist(A1, h1)+dist(A2, h1), dist(A1, h1)+dist(h1, h2)+dist(B1, h2)));
				}
			}
		}
	}

	printf("%d\n", ans);
}
