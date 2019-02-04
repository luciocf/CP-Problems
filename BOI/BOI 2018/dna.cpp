// BOI 2018 - DNA
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 2e5+10;

int num[MAXN], freq[MAXN], M[MAXN], n, k, m;

bool is[MAXN];

pii q[MAXN];

bool ok(int x)
{
	memset(freq, 0, sizeof freq);
	int qtd = 0;

	int l = 1, r = x;
	for (int i = l; i <= r; i++)
	{
		if (is[num[i]]) freq[num[i]]++;
		if (is[num[i]] && freq[num[i]] == q[M[num[i]]].second) qtd++;
	}
	if (qtd == m) return true;

	while (r < n)
	{
		if (is[num[l]] && freq[num[l]] == q[M[num[l]]].second) qtd--;
		freq[num[l]]--, l++, r++;

		if (is[num[r]] && freq[num[r]]+1 == q[M[num[r]]].second) qtd++;
		freq[num[r]]++;

		if (qtd == m) return true;
	}

	return false;
}

int busca(void)
{
	int ini = 1, fim = n, ans = -1;
	while (ini <= fim)
	{
		int mid = (ini+fim)/2;

		if (ok(mid)) fim = mid-1, ans = mid;
		else ini = mid+1;
	}
	return ans;
}

int main(void)
{
	cin >> n >> k >> m;

	for (int i = 1; i <= n; i++)
		cin >> num[i];

	for (int i = 1; i <= m; i++)
	{
		int x;
		cin >> q[i].first >> q[i].second;
		is[q[i].first] = 1;
		M[q[i].first] = i;
	}

	int ans = busca();
	if (ans == -1) cout << "impossible\n";
	else cout << ans << "\n";
}
