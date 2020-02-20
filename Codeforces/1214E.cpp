// Codeforces 1214E - Petya and Construction Set
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> pii;

bool comp(pii a, pii b)
{
	return a.first > b.first;
} 

pii a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].first);
		a[i].second = 2*i-1;
	}

	sort(a+1, a+n+1, comp);

	vector<int> linha;
	vector<pii> edge;

	for (int i = 1; i <= n; i++)
	{
		linha.push_back(a[i].second);

		if (i < n) edge.push_back({a[i].second, a[i+1].second});
	}

	for (int i = 1; i <= n; i++)
	{
		int x = a[i].second+1;
		int dist = a[i].first;

		edge.push_back({x, linha[i-1+dist-1]});

		if (i-1+dist-1 == linha.size()-1) linha.push_back(x);
	}

	for (auto e: edge)
		printf("%d %d\n", e.first, e.second);
}
