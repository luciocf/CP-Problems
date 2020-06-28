// OII 2018 - Cena di Gala
// Lúcio Cardoso

// Solution is the same as: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Cena/main.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int onde[maxn], ind[maxn];

int aux[maxn];

vector<int> pos[maxn];

long long conta(int S, int s[], int P, int p[])
{
	for (int i = 0; i < S; i++)
		pos[s[i]].push_back(i);

	int at = 0;
	for (int i = 0; i < S; i++)
	{
		if (at == P) break;

		if (s[i] == p[at])
		{
			onde[at] = i, ind[at] = aux[s[i]];
			++at;
		}

		aux[s[i]]++;
	}

	if (at != P) return 0;

	ll ans = 1ll*(S-onde[P-1]);

	for (int l = 0; l < S; l++)
	{
		if (onde[0] != l)
		{
			ans += 1ll*(S-onde[P-1]);
			continue;
		}

		if (ind[0] == pos[p[0]].size()-1) break;

		ind[0]++;
		onde[0] = pos[p[0]][ind[0]];

		bool ok = true;
		for (int i = 1; i < P; i++)
		{
			if (onde[i] > onde[i-1]) break;
			if (pos[p[i]].back() <= onde[i-1]) return ans;

			while (onde[i] <= onde[i-1] && ind[i] < (int)pos[p[i]].size()-1)
			{
				ind[i]++;
				onde[i] = pos[p[i]][ind[i]];
			}
		}

		ans += 1ll*(S-onde[P-1]);
	}

	return ans;
}
