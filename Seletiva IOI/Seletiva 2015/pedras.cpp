// Seletiva IOI 2015 - Pedras (versão online)
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;
const int MAXR = 320;

int num[MAXN], b[MAXR][MAXR], pref[MAXN][MAXR], freq[MAXN][MAXR], n, q, s;
int resp[MAXN];

void pre(void)
{
	for (int i = 1; i <= n/s; i++)
	{
		for (int j = 0; j+i <= n/s; j++)
		{
			int x = j+i;
			int ans = b[j][x-1], aux;
			for (int k = x*s; k < min(n, (x+1)*s); k++)
			{
				if (!j) aux = pref[num[k]][x];
				else aux = pref[num[k]][x]-pref[num[k]][j-1];
				ans = max(ans, aux);
			}
			b[j][x] = ans;
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &q);
	s = sqrt(n);

	map<int, int> M;
	vector<int> v;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num[i]);
		v.push_back(num[i]);
	}

	sort(v.begin(), v.end());

	int count = -1;
	for (int i = 0; i < v.size(); i++)
		if (M.find(v[i]) == M.end()) M[v[i]] = ++count;

	for (int i = 0; i < n; i++)
	{
		num[i] = M[num[i]];
		freq[num[i]][i/s]++;
		b[i/s][i/s] = max(b[i/s][i/s], freq[num[i]][i/s]);
	}

	for (int i = 0; i < n; i++)
	{
		pref[i][0] = freq[i][0];
		for (int j = 1; j <= n/s; j++)
			pref[i][j] = pref[i][j-1]+freq[i][j];
	}
	pre();

	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		l--, r--;

		int k = l/s, p = r/s;

		if (k == p)
		{
			int ans = 0;

			for (int i = l; i <= r; i++) resp[num[i]] = 0;
			for (int i = l; i <= r; i++) resp[num[i]]++, ans = max(ans, resp[num[i]]);
			printf("%d\n", ans);
			continue;
		}
		int ans = b[k+1][p-1];

		for (int i = l; i < (k+1)*s; i++) resp[num[i]] = pref[num[i]][p-1]-pref[num[i]][k];
		for (int i = p*s; i <= r; i++) resp[num[i]] = pref[num[i]][p-1]-pref[num[i]][k];

		for (int i = l; i < (k+1)*s; i++) resp[num[i]]++, ans = max(ans, resp[num[i]]);
		for (int i = p*s; i <= r; i++) resp[num[i]]++, ans = max(ans, resp[num[i]]);

		printf("%d\n", ans);
	}
}
