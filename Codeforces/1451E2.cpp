// Codeforces 1451E2 - Bitwise Queries (Hard Version)
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];
int sei[17];

int onde[maxn];

int v[maxn];

int ask(int i, int j, int q)
{
	if (q == 0) cout << "XOR " << i << " " << j << endl;
	else cout << "AND " << i << " " << j << endl;

	int p;
	cin >> p;
	return p;
}

int main(void)
{
	int n;
	cin >> n;

	int id1, id2;
	int found = -1;

	onde[0] = 1;

	for (int i = 2; i <= n; i++)
	{
		v[i] = ask(1, i, 0);

		if (v[i] == n-1) id1 = i;
		if (v[i] != n-1) id2 = i;

		if (found == -1 && onde[v[i]])
		{
			a[1] = ask(i, onde[v[i]], 1) ^ v[i];
			found = i;
		}

		onde[v[i]] = i;
	}

	if (found != -1)
	{
		for (int i = 2; i <= n; i++)
			a[i] = v[i] ^ a[1];

		cout << "!";
		for (int i = 1; i <= n; i++)
			cout << " " << a[i];
		cout << endl;

		return 0;
	}

	int x = ask(1, id2, 1);

	for (int i = 0; i < 16; i++)
	{
		sei[i] = 2;

		if (x&(1<<i)) sei[i] = 1;
		else if (!(v[id2]&(1<<i))) sei[i] = 0;
	}

	int p1 = v[id1], p2 = 0, p3 = ask(id1, id2, 1);

	for (int i = 0; i < 16; i++)
	{
		if (sei[i] == 0 && (p1&(1<<i))) a[id1] += (1<<i);
		else if (sei[i] == 1 && (!(p1&(1<<i)))) a[id1] += (1<<i);
		else if (sei[i] == 2 && ((p2&(1<<i)) || (p3&(1<<i)))) a[id1] += (1<<i);
	}

	for (int i = 0; i < 16; i++)
	{
		if ((p1&(1<<i)) && (!(a[id1]&(1<<i)))) a[1] += (1<<i);
		if ((!(p1&(1<<i))) && (a[id1]&(1<<i))) a[1] += (1<<i);
	}

	for (int i = 2; i <= n; i++)
		a[i] = v[i] ^ a[1];

	cout << "!";
	for (int i = 1; i <= n; i++)
		cout << " " << a[i];
	cout << endl;
}
