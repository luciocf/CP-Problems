// IOI 2000 - Median
// Lúcio Cardoso

// Solution is the same as in: https://github.com/peon-pasado/CompetitiveProgramming/blob/master/dunjudge/median/ans.cpp

#include <bits/stdc++.h>
#include "device.h"

using namespace std;

int Med3(int a, int b, int c);

int solve(int n, vector<int> L, vector<int> M, vector<int> R, int a, int b)
{
	if (L.size() == n/2) return a;
	if (R.size() == n/2) return b;

	if (R.size() > L.size())
	{
		swap(L, R);
		swap(a, b);
	}

	vector<int> S1, S2;

	if (L.size() > n/2)
	{
		int k = L[rand()%((int)L.size())];
		
		for (auto x: L)
		{
			if (x == k) continue;

			if (Med3(k, x, a) == k) S1.push_back(x);
			else S2.push_back(x);
		}

		L.clear();

		for (auto x: M)
			L.push_back(x);
		L.push_back(b);
		for (auto x: R)
			L.push_back(x);

		return solve(n, L, S2, S1, a, k);
	}
	else
	{
		R.push_back(b);
        b = M[rand()%((int)M.size())];

        for (auto x: M)
        {
            if (x == b) continue;

            if (Med3(a, b, x) == b) S1.push_back(x);
            else S2.push_back(x);
        }

        if (S1.size() + R.size() > n/2)
        {
            M = S1;

            for (int x: S2)
            	L.push_back(x);
            L.push_back(a);

            a = b; b = R.back();
            R.pop_back();

            return solve(n, L, M, R, a, b);
        }
        else
        {
            M = S2;

            for (int x: S1)
            	R.push_back(x);

            return solve(n, L, M, R, a, b);
        }
	}
}

int Median(int n)
{
	srand(time(0));

	int a = rand()%n+1, b = rand()%n+1;
	while (a == b) b = rand()%n+1;

	vector<int> L, M, R;

	for (int i = 1; i <= n; i++)
	{
		if (i == a || i == b) continue;

		int med = Med3(a, b, i);

		if (med == a) L.push_back(i);
		else if (med == b) R.push_back(i);
		else M.push_back(i);
	}

    return solve(n, L, M, R, a, b);
}
