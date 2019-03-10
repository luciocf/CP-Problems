// IOI 2014 - Gondola
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "gondola.h"

using namespace std;

const int mod = 1e9+9;

typedef long long ll;

typedef pair<int, int> pii;

int valid(int n, int inputSeq[])
{
	int g[n+1];
	
	map<int, bool> mark;

	int first = -1;

	for (int i = 0; i < n; i++)
	{
		g[i] = inputSeq[i];

		if (mark[g[i]]) return 0;
		mark[g[i]] = 1;

		if (g[i] <= n && first == -1) first = i;
	}

	int cur = g[first];

	for (int i = first+1; i < n; i++)
	{
		cur = (cur == n ? 1 : cur+1);
		if (g[i] <= n && g[i] != cur) return 0;
	}

	for (int i = 0; i < first; i++)
	{
		cur = (cur == n ? 1 : cur+1);
		if (g[i] <= n && g[i] != cur) return 0;
	}

	return 1;
}

//----------------------

int replacement(int n, int gondolaSeq[], int replacementSeq[])
{
	int g[n+1], ind[n+1];

	int first = -1;

	for (int i = 0; i < n; i++)
	{
		g[i] = gondolaSeq[i];

		if (g[i] <= n && first == -1) first = i;
	}

	if (first == -1)
	{
		for (int i = 0; i < n; i++)
			ind[i] = i+1;
	}
	else
	{
		int cur = g[first];

		for (int i = first+1; i < n; i++)
		{
			cur = (cur == n ? 1 : cur+1);

			ind[i] = cur;
		}

		for (int i = 0; i < first; i++)
		{
			cur = (cur == n ? 1 : cur+1);

			ind[i] = cur;
		}
	}

	int l = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;

	for (int i = 0; i < n; i++) if (g[i] > n) pq.push({g[i], i});

	int cur = n+1;
	while (!pq.empty())
	{
		int v = pq.top().first, i = pq.top().second;
		pq.pop();

		replacementSeq[l++] = ind[i];
		
		while (cur < v) 
			replacementSeq[l++] = cur++;
		cur++;
	}

	return l;
}

//----------------------

ll pot(ll a, ll b)
{
	if (!b) return 1ll;

	ll t = pot(a, b/2);

	if (b%2 == 0) return (t*t)%mod;
	return (a*((t*t)%mod))%mod;
}

int countReplacement(int n, int inputSeq[])
{
	if (!valid(n, inputSeq)) return 0;

	int last = n+1, less;
	ll ans = 1ll;

	bool dif = 0;

	sort(inputSeq, inputSeq+n);

	int pos = n+1;

	for (int i = 0; i < n; i++)
	{
		if (inputSeq[i] > n && pos == n+1) pos = i;
		else if (inputSeq[i] <= n) dif = 1;
	}

	less = n-pos;

	for (int i = pos; i < n; i++)
	{
		int v = inputSeq[i];

		ans = (ans*pot(1ll*less, 1ll*(v-last)))%mod;

		last = v+1, less--;
	}

	if (!dif)
	{
		ans = (ans*1ll*n)%mod;
	}

	return ans;
}
