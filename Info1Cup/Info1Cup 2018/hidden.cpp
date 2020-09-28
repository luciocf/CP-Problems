// Info(1) Cup 2018 - Hidden Sequence
// Lúcio Cardoso

// Solution is the same as in: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Info1Cup/2018%20-%20International%20Round/Info1Cup%2018-Hidden.cpp

#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

bool is(int q_0, int q_1, bool ord)
{
	vector<int> v;

	if (ord)
	{
		for (int i = 0; i < q_1; i++)
			v.push_back(1);
		for (int i = 0; i < q_0; i++)
			v.push_back(0);
	}
	else
	{
		for (int i = 0; i < q_0; i++)
			v.push_back(0);
		for (int i = 0; i < q_1; i++)
			v.push_back(1);
	}

	return isSubsequence(v);
}

vector<int> findSequence (int n)
{
	vector<int> ans;

	int tot_0 = 0, tot_1 = 0;

	if (is(0, n/2+1, 1))
	{
		for (int i = 1; i <= n/2; i++)
			if (is(i, 0, 0))
				tot_0 = i;

		tot_1 = n-tot_0;
	}
	else
	{
		for (int i = 1; i <= n/2; i++)
			if (is(0, i, 1))
				tot_1 = i;

		tot_0 = n-tot_1;
	}

	int qtd_0 = 0, qtd_1 = 0;

	for (int i = 0; i < n; i++)
	{
		if (qtd_1+1 + tot_0-qtd_0 <= n/2+1)
		{
			if (is(tot_0-qtd_0, qtd_1+1, 1))
			{
				ans.push_back(1);
				qtd_1++;
			}
			else
			{
				ans.push_back(0);
				qtd_0++;
			}
		}
		else
		{
			if (is(qtd_0+1, tot_1-qtd_1, 0))
			{
				ans.push_back(0);
				qtd_0++;
			}
			else
			{
				ans.push_back(1);
				qtd_1++;
			}
		}
	}

	return ans;
}

