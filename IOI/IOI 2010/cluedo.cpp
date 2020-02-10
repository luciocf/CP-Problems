// IOI 2010 - Cluedo
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "grader.h"
#include "cluedo.h"

bool mark1[7], mark2[10], mark3[7];

void Solve()
{
	memset(mark1, 0, sizeof mark1);
	memset(mark2, 0, sizeof mark2);
	memset(mark3, 0, sizeof mark3);

	while (true)
	{
		for (int i = 1; i <= 6; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				for (int k = 1; k <= 6; k++)
				{
					if (mark1[i] || mark2[j] || mark3[k]) continue;

					int guess = Theory(i, j, k);

					if (guess == 0) return;
					else if (guess == 1) mark1[i] = 1;
					else if (guess == 2) mark2[j] = 1;
					else mark3[k] = 1;
				}
			}
		}
	}
}
