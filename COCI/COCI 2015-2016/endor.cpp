// COCI 2015/2016 - Endor
// Lúcio Cardoso

// Solution:

// 1. Notice that a -> with value A colliding with a <- with value B can be seen as -> just passing by
// maintaining its value and <- becomes (a+b)%k.

// 2. After this, add (L-d) to the answer of all -> in position d. Now, we want to update the answers
// for every intersection of a <- with a ->.

// 3. If a <- with color A turns out to have color B after some intersections, we know that
// B = A + pref_last - pref_j, where last is the last -> before the <- being seen, j is the index of <-
// and pref_i is the sum of all colors until the ith ->.

// 4. If a <- in positon x intersects with a -> in position y, and z is the first -> before y, then the
// amount the color in x is going to win is (x-z)/2 - (x-y)/2 = (y-z)/2. Thus, we only need to store this value
// in an array for all prefixes, and, for a fixed <-, see how much each of its different possible K colors can win.

// Complexity: O(nk) 

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

struct P
{
	int d, t;
	char c;
} a[maxn];

double ans[maxn], soma[maxn];

int main(void)
{
	int n, k, l;
	scanf("%d %d %d", &n, &k, &l);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %c", &a[i].d, &a[i].t, &a[i].c);

	int last = -1, first = -1, pref = 0;

	for (int i = 1; i <= n; i++)
	{
		if (a[i].c == 'D')
		{
			if (last == -1) first = a[i].d;
			else soma[(k-pref)%k] += (double)(a[i].d-last)/2;

			last = a[i].d, pref = (pref+a[i].t)%k;

			ans[a[i].t] += (l-a[i].d);
		}
		else
		{
			if (last == -1) ans[a[i].t] += a[i].d;
			else
			{
				ans[a[i].t] += (double)(a[i].d-last)/2;
				ans[(pref+a[i].t)%k] += ((double)(a[i].d-first)/2 + (double)first);

				for (int j = 0; j < k; j++)
					ans[(a[i].t + pref + k - j)%k] += soma[(k-j)%k];
			}
		}
	}

	for (int i = 0; i < k; i++)
		printf("%.1lf\n", ans[i]);
}
