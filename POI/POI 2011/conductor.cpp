// POI 2011 - Lightning Conductor
// Lúcio Cardoso

// Solution: https://github.com/MohamedAhmed04/Competitive-programming/blob/master/POI/POI11_pio-Conductor.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n;
int h[maxn];

int L[maxn], R[maxn];

void get_candidates(void)
{
	int last = -1;

	for (int i = 1; i <= n; i++)
	{
		if (h[i] <= last) continue;
		last = h[i];

		for (int d = 1; i + (d-1)*(d-1) + 1 <= n; d++)
		{
			int p = i + (d-1)*(d-1) + 1;
			L[p] = max(L[p], h[i]+d);
		}
	}

	last = -1;

	for (int i = n; i >= 1; i--)
	{
		if (h[i] <= last) continue;
		last = h[i];

		for (int d = 1; i - (d-1)*(d-1) - 1 > 0; d++)
		{
			int p = i - (d-1)*(d-1) - 1;
			R[p] = max(R[p], h[i]+d);
		}
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);

	get_candidates();

	for (int i = 1; i <= n; i++) L[i] = max(L[i-1], L[i]);
	for (int i = n; i >= 1; i--) R[i] = max(R[i+1], R[i]);

	for (int i = 1; i <= n; i++)
		printf("%d\n", max(0, max(R[i], L[i])-h[i]));
}
