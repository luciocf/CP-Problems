// CEOI 2013 - Treasure
// Lúcio Cardoso

// Solution:

/* 1. If we calculate the prefix subrectangle for every point, it's simple to calculate
   the value in that point using inclusion-exclusion.

   2. Instead of directly asking the query (1, 1, i, j) for every point (i, j), we can ask
   the query using the largest subrectangle which contains that point and one of the four corners.
   Essentialy, we divide the rectangle in four quadrants and use one of the four corners to ask a query
   depending on the quadrant.

   3. After that, it's simple to calculate the prefix for each point depending on its quadrant.

   Complexity: O(n²)
*/

#include <bits/stdc++.h>
#include "treasure.h"

const int maxn = 110;

int pref[maxn][maxn];

void findTreasure(int N) 
{
	for (int i = N; i >= 1; i--)
	{
		for (int j = N; j >= 1; j--)
		{
			if (i > N/2 && j > N/2)
				pref[i][j] = countTreasure(1, 1, i, j);
			else if (i > N/2 && j <= N/2)
				pref[i][j] = pref[i][N] - countTreasure(1, j+1, i, N);
			else if (i <= N/2 && j <= N/2)
				pref[i][j] = pref[i][N] + pref[N][j] + countTreasure(i+1, j+1, N, N) - pref[N][N];
			else
				pref[i][j] = pref[N][j] - countTreasure(i+1, 1, N, j);
		}
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (pref[i][j]-pref[i-1][j]-pref[i][j-1]+pref[i-1][j-1] == 1)
				Report(i, j);
}
