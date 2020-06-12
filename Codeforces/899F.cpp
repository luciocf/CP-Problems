// Codeforces 899F - Letters Removing
// Lúcio Cardoso

// Solution is the same as editorial, using a BIT

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

char a[maxn];

int bit[maxn];

bool mark[maxn];

set<int> st[100];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int busca(int x)
{
	int soma = 0, pos = 0;

	for (int i = 20; i >= 0; i--)
		if (pos + (1<<i) < maxn && soma + bit[pos+(1<<i)] < x)
			pos += (1<<i), soma += bit[pos];

	return pos+1;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int aux = 0;
	map<char, int> mp;

	for (char i = 'a'; i <= 'z'; i++)
		mp[i] = ++aux;
	for (char i = 'A'; i <= 'Z'; i++)
		mp[i] = ++aux;
	for (char i = '0'; i <= '9'; i++)
		mp[i] = ++aux;

	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);

		a[i] = c;

		st[mp[c]].insert(i);
		upd(i, 1);
	}

	while (m--)
	{
		int l, r;
		char c;
		scanf("%d %d %c", &l, &r, &c);

		int ind = mp[c];

		l = busca(l);
		r = busca(r);

		for (auto it = st[ind].lower_bound(l); it != st[ind].end() && *it <= r; )
		{
			upd(*it, -1);
			mark[*it] = 1;

			it = st[ind].erase(it);
		}
	}

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			printf("%c", a[i]);
	printf("\n");
}
