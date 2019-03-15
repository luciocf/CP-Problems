// IOI 2015 - Sorting
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "sorting.h"

using namespace std;

const int maxn = 2e5+10;
const int maxm = 6e5+10;

typedef pair<int, int> pii;

int s[maxn], final[maxn], pos[maxn], pos_final[maxn];

// checa se S está ordenado
bool check(int N)
{
	for (int i = 0; i < N; i++)
		if (s[i] != i) return false;

	return true;
}

// Faz a operação de trocar os índices
void replace(int i, int j, bool q)
{
	int a, b;
	
	if (q)
	{
		a = s[i], b = s[j];

		s[i] = b, s[j] = a;

		pos[a] = j, pos[b] = i;
	}
	else
	{
		a = final[i], b = final[j];

		final[i] = b, final[j] = a;

		pos_final[a] = j, pos_final[b] = i;
	}
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[])
{	
	for (int i = 0; i < N; i++)
		final[i] = s[i] = S[i], pos_final[s[i]] = pos[s[i]] = i;

	if (check(N)) return 0;

	int ini = 1, fim = N+1, ans = N+1;

	vector<int> curP(M), curQ(M);

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		for (int i = 0; i < N; i++)
			final[i] = s[i] = S[i], pos_final[s[i]] = pos[s[i]] = i;

		for (int i = 0; i < mid; i++)
			replace(X[i], Y[i], 0);

		int first = 0;
		for (int j = 0; j < mid; j++)
		{
			replace(X[j], Y[j], 1);

			for (int i = first; i < N; i++)
			{
				if (final[i] == i)
				{
					first++;
					curP[j] = curQ[j] = 0;
					continue;
				}

				curP[j] = pos[i], curQ[j] = pos[final[i]];
				replace(curP[j], curQ[j], 1);
				replace(pos_final[i], i, 0);

				first++;

				break;
			}
		}

		if (check(N))
		{
			fim = mid-1, ans = mid;
			for (int i = 0; i < ans; i++)
				P[i] = curP[i], Q[i] = curQ[i];
		}
		else ini = mid+1;
	}
	
	return ans;
}
