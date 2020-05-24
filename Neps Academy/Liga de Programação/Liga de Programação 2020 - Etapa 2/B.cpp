// Neps Academy - Liga de Programação 2020 - Etapa 2 - Rank do Nepscord
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first

using namespace std;

const int maxn = 1e3+10;

map<string, int> last;
map<string, int> xp;
map<string, int> ini;

vector<pair<int, string>> V;

bool comp(pair<int, string> a, pair<int, string> b)
{
	if (a.first == b.first) return a.second > b.second;
	return a.first < b.first;
}

int main(void)
{
	int n, k;
	cin >> n >> k;

	int aux = 0;

	for (int i = 1; i <= n; i++)
	{
		string s;
		int m;
		cin >> s >> m;

		if (!ini[s])
		{
			ini[s] = 1;
			last[s] = m, xp[s] += 25;
		}
		else
		{
			if (last[s] <= m-k)
			{
				last[s] = m;
				xp[s] += 25;
			}
		}
	}

	for (auto pp: xp)
		V.push_back({pp.second, pp.first});

	sort(V.begin(), V.end(), comp);

	printf("--Rank do Nepscord--\n");

	if (V.size() == 1)
	{
		cout << "#1. " << V.back().second << " - Nivel " << V.back().ff/100 + 1 << "\n";
		cout << "#2.\n#3.\n";
	}
	else if (V.size() == 2)
	{
		cout << "#1. " << V.back().second << " - Nivel " << V.back().ff/100 + 1<< "\n";
		cout << "#2. " << V[V.size()-2].second << " - Nivel " << V[V.size()-2].ff/100  + 1<< "\n";
		cout << "#3.\n";
	}
	else
	{
		cout << "#1. " << V.back().second << " - Nivel " << V.back().ff/100 + 1 << "\n";
		cout << "#2. " << V[V.size()-2].second << " - Nivel " << V[V.size()-2].ff/100 + 1 << "\n";
		cout << "#3. " << V[V.size()-3].second << " - Nivel " << V[V.size()-3].ff/100 + 1<< "\n";
	}
}
